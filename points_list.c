#include "points_list.h"

void check_point_list_on_null(const char *fname, PointsList *list) {
    if (list == NULL) {
        fprintf(stderr, "%s interrupted\nPointsList is NULL\n", fname);
        exit(EXIT_FAILURE);
    }
}


PointsList* create_points_list(size_t start_capacity, int nb_classes, int dimensions) {
    PointsList *res;

    if ((res = (PointsList*) malloc(sizeof(PointsList))) == NULL) {
        fprintf(stderr, "Error while memory allocation\n");
        return NULL;
    }

    if ((res->points = (Point**) malloc(sizeof(Point*) * start_capacity)) == NULL) {
        fprintf(stderr, "Error while memory allocation\n");
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
    Point **tmp;

    check_point_list_on_null("points_list_add_point", list);
    check_point_on_null("points_list_add_point", point);

    if (list->count == list->capacity) {
        list->capacity = list->capacity * 2 + 1;

        Point **tmp = (Point **) realloc(list->points, sizeof(Point*) * list->capacity);
        if (tmp == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        list->points = tmp;
    }

    list->points[list->count] = point;
    list->count++;
}

void points_list_remove_point(PointsList *list, size_t index) {
    Point *tmp;

    check_point_list_on_null("points_list_remove_point", list);

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

    check_point_list_on_null("points_list_get_point", list);

    if (list->count <= index) {
        fprintf(stderr, "Error points_list_get_point. Index out of range\n");
        exit(EXIT_FAILURE);
    }
    return list->points[index];
}

void points_list_set_point(PointsList *list, size_t index, Point *p) {
    
    check_point_list_on_null("points_list_set_point", list);

    if (list->count <= index) {
        fprintf(stderr, "Error points_list_set_point. Index out of range\n");
        exit(EXIT_FAILURE);
    }

    free_point(list->points[index]);

    list->points[index] = p;
}

size_t points_list_get_count(PointsList *list) {

    check_point_list_on_null("points_list_get_count", list);

    if (list == NULL)
        return 0;
    return list->count;
}

void fprint_points_list(FILE *file, PointsList *list) {
    size_t i;

    if (list != NULL) {
        fprintf(file, "Points list: [%ld %d %d]\n", list->count, list->nb_classes, list->dimensions);
        for (i = 0; i < list->count; i++)
            fprint_point(file, list->points[i]);
    } else {
        fprintf(file, "Points List is NULL\n");
    }
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

int extract_majority_class_from_stack(Stack *stack, int nb_classes) {
    int *classes_count;
    int best_class, best_count, tmp_class;
    PointDistance *tmp_point;

    if (nb_classes < 1 || stack == NULL) {
        free_stack(stack);
        return -1;
    }

    if ((classes_count = (int*) calloc(nb_classes, sizeof(int))) == NULL) {
        fprintf(stderr, "Error while memory allocation");
        return -1;
    }

    best_class = 0;
    best_count = 0;

    while (!stack_is_empty(stack)) {
        tmp_point = stack_pop(stack);



        tmp_class = get_point_classe(tmp_point->point);

        
        if (tmp_class > 0 && tmp_class <= nb_classes) {
            classes_count[tmp_class - 1]++;

            if (classes_count[tmp_class - 1] >= best_count) {
                best_class = tmp_class;
                best_count = classes_count[tmp_class - 1];
            }
        }

        free(tmp_point);
    }

    /* free memory */
    free(classes_count);

    return best_class;  
}

Stack* point_list_select_k_nearby(PointsList *list, Point *target, int k) {
    Stack *res;
    OrderedPointsList *order_list;
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
    int best_class;

    if (k < 1 || list == NULL || target == NULL)
        return -1;

    best_stack = point_list_select_k_nearby(list, target, k);
    best_class = extract_majority_class_from_stack(best_stack, list->nb_classes);

    free_stack(best_stack);
    set_point_classe(target, k);

    return best_class;  
}