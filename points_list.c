#include "points_list.h"

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