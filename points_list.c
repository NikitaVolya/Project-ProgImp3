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

OrderedPoinstList* create_ordered_point_list(size_t maxsize) {
    OrderedPoinstList* res;

    if ((res = (OrderedPoinstList*) malloc(sizeof(OrderedPoinstList))) == NULL) {
        return NULL;
    }
    res->maxsize = maxsize;
    res->best_stack = create_stack();
    res->tmp_stack = create_stack();

    return res;
}

void free_ordered_points_list(OrderedPoinstList* list) {
    free_stack(list->best_stack);
    free_stack(list->tmp_stack);
    free(list);
}

OrderedPoinstList* ordered_points_list_add_point(OrderedPoinstList* list, Point *point, Point *target) {
    PointDistance *pointDist;
    
    pointDist = create_point_distatnce(point, target);

    /* transfer all points with grater distance than point to tmp_stack from best_stack */
    while (!stack_is_empty(list->best_stack) && 
        ((PointDistance*) stack_value(list->best_stack))->distance > pointDist->distance) {
        stack_push(list->tmp_stack, stack_pop(list->best_stack));
    }

    /* add point to best_stack if enough place */
    if (get_stack_size(list->best_stack) < list->maxsize) {
        stack_push(list->best_stack, pointDist);
    }

    /* add points from tmp_stack to best_stack if enough place */
    while (!stack_is_empty(list->tmp_stack) && 
            get_stack_size(list->best_stack) < list->maxsize) {
        stack_push(list->best_stack, stack_pop(list->tmp_stack));
    }

    /* clear tmp_stack */
    stack_clear(list->tmp_stack);

    return list;
}

Stack* extract_points(OrderedPoinstList *list) {
    Stack *res;

    res = list->best_stack;
    list->best_stack = create_stack();

    return res;
}

Stack* get_points(OrderedPoinstList *list) {
    return list->best_stack;
}

Point* get_ordered_points_first_point(OrderedPoinstList* list) {
    if (stack_is_empty(list->best_stack))
        return NULL;
    else
        return stack_value(list->best_stack);
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

void points_list_set_point(PointsList *list, size_t index, Point *p) {
    if (list->count <= index) {
        fprintf(stderr, "Error points_list_set_point. Index out of range\n");
        exit(EXIT_FAILURE);
    }
    list->points[index] = p;
}

size_t points_list_get_count(PointsList *list) {
    if (list == NULL)
        return 0;
    return list->count;
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

Stack* point_list_select_k_nearby(PointsList *list, Point *target, int k) {
    Stack *res;
    OrderedPoinstList *order_list;
    size_t i;
    
    if (k < 1 || list == NULL || target == NULL)
        return NULL;

    order_list = create_ordered_point_list(k);

    for (i = 0; i < list->count; i++) {
        ordered_points_list_add_point(order_list, list->points[i], target);
    }

    res = extract_points(order_list);
    free_ordered_points_list(order_list);

    return res;  
}

int select_class_bf(PointsList *list, Point *target, int k) {
    Stack *best_stack;
    PointDistance *tmp_point;
    short *classes_count;
    int best_class, best_count, tmp_class;

    if (k < 1 || list == NULL || target == NULL)
        return -1;

    if ((classes_count = (short*) calloc(list->nb_classes, sizeof(short))) == NULL) {
        fprintf(stderr, "Error while memory allocation");
        return -1;
    }

    best_stack = point_list_select_k_nearby(list, target, k);
    
    best_class = 0;
    best_count = 0;

    printf("================= NEIBORS ======================\n");

    /* counting points and chosing best class */
    while (!stack_is_empty(best_stack)) {
        tmp_point = stack_pop(best_stack);
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
    free(classes_count);

    set_point_classe(target, best_class);

    return best_class;  
}