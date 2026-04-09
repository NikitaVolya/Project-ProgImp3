#include "points_list.h"


PointDistance* create_point_distatnce(Point* target, Point *point) {
    PointDistance* res;

    if ((res = (PointDistance*) malloc(sizeof(PointDistance))) == NULL) {
        return NULL;
    }
    res->point = target;
    res->distance = get_distance_to_point(target, point);
    return res;
}

PointsList* create_points_list(size_t start_capacity, int nb_classes, int dimensions) {
    PointsList *res;

    if ((res = (PointsList*) malloc(sizeof(PointsList))) == NULL ||
        (res->points = (Point**) malloc(sizeof(Point*) * start_capacity)) == NULL) {
        fprintf(stderr, "Error while memory allocation\n");
        if (res != NULL) 
            free(res);
        return NULL;
    }

    res->capacity = start_capacity;
    res->count = 0;
    res->nb_classes = nb_classes;
    res->dimensions = dimensions;

    return res;
}


void points_list_add_point(PointsList *list, Point *point) {

    if (list == NULL) {
        fprintf(stderr, "list is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (point == NULL) {
        fprintf(stderr, "point is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (list->count == list->capacity) {
        list->capacity = list->capacity * 2 + 1;
        list->points = realloc(list->points, sizeof(Point*) * list->capacity);
    }

    list->points[list->count] = point;
    list->count++;
}


void points_list_remove_point(PointsList *list, size_t index) {
    Point *tmp;

    if (list->count <= index) {
        fprintf(stderr, "Error points_list_remove_point. Index out of range\n");
        exit(EXIT_FAILURE);
    }

    
    tmp = list->points[index];

    if (list->count != 1) {
        list->points[index] = list->points[list->count - 1];
    }
    
    free_point(tmp);
    list->count--;
} 

Point* points_list_get_point(PointsList *list, size_t index) {
    if (list->count <= index) {
        fprintf(stderr, "Error points_list_get_point. Index out of range\n");
        exit(EXIT_FAILURE);
    }
    return list->points[index];
}

void fprint_points_list(FILE *file, PointsList *list) {
    size_t i;

    fprintf(file, "Points list: [%ld %d %d]\n", list->count, list->nb_classes, list->dimensions);
    for (i = 0; i < list->count; i++)
        fprint_point(file, list->points[i]);
}

void print_points_list(PointsList *list) {
    fprint_points_list(stdout, list);
}

void free_points_list(PointsList *list) {
    size_t i;

    for (i = 0; i < list->count; i++) {
        free_point(list->points[i]);
    }
    free(list->points);
    free(list);
}

int select_class_bf(PointsList *list, Point *target, int k) {
    Stack *best_stack, *tmp_stack;
    PointDistance *point, *tmp_point;
    size_t i;
    short *classes_count;
    int best_class, best_count, tmp_class;
    double progress_step, progress;
    int j, print_progress;
    
    if (k < 1 || list == NULL || target == NULL)
        return -1;

    if ((classes_count = (short*) calloc(list->nb_classes, sizeof(short))) == NULL) {
        fprintf(stderr, "Error while memory allocation");
        return -1;
    }

    best_stack = create_stack();
    tmp_stack = create_stack();

    progress = 0.f;
    print_progress = 0;
    progress_step = PROGRESSBAR_SIZE / (double) list->count;


    for (i = 0; i < list->count; i++) {
        /* selecting point and find distance from target */
        point = create_point_distatnce(list->points[i], target);

        if (print_progress < (int) progress) {
            print_progress = (int) progress;

            putc('|', stdout);
            for (j = 0; j < PROGRESSBAR_SIZE; j++) {
                if (j <= (int) progress - progress_step)
                    putc('#', stdout);
                else
                    putc(' ', stdout);
            }
            putc('|', stdout);
            putc('\n', stdout);
        }

        /* transfer all points with grater distance than point to tmp_stack from best_stack */
        while (!stack_is_empty(best_stack) && 
              ((PointDistance*) stack_value(best_stack))->distance > point->distance) {
            stack_push(tmp_stack, stack_pop(best_stack));
        }

        /* add point to best_stack if enough place */
        if (get_stack_size(best_stack) < (size_t) k) {
            stack_push(best_stack, point);
        }

        /* add points from tmp_stack to best_stack if enough place */
        while (!stack_is_empty(tmp_stack) && get_stack_size(best_stack) < (size_t) k) {
            stack_push(best_stack, stack_pop(tmp_stack));
        }

        /* clear tmp_stack */
        stack_clear(tmp_stack);

        progress += progress_step;
    }

    best_class = -1;
    best_count = 0;

    printf("================= NEIBORS ======================\n");

    /* counting points and chosing best class */
    while (!stack_is_empty(best_stack)) {
        tmp_point = stack_pop(best_stack);
        printf("%f <=> ", tmp_point->distance);
        print_point(tmp_point->point);

        tmp_class = get_point_classe(tmp_point->point);
        classes_count[tmp_class - 1]++;

        if (classes_count[tmp_class - 1] >= best_count) {
            best_class = tmp_class;
            best_count = classes_count[tmp_class - 1];
        }
        free(tmp_point);
    }

    /* free memory */
    free_stack(best_stack);
    free_stack(tmp_stack);
    free(classes_count);

    set_point_classe(target, best_class);

    return best_class;  
}