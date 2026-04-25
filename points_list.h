#ifndef _POINTS_LIST_H_
#define _POINTS_LIST_H_

#include<stdlib.h>
#include<stdio.h>
#include"point.h"
#include"stack.h"

#define PROGRESSBAR_SIZE 50

typedef struct {
    Point **points;
    size_t capacity, count;
    int nb_classes, dimensions;
} PointsList;

typedef struct {
    Point *point;
    double distance;
} PointDistance;

PointDistance* create_point_distatnce(Point* target, Point *point);

PointsList* create_points_list(size_t start_capacity, int nb_classes, int dimensions);

void points_list_add_point(PointsList *list, Point *point);

void points_list_remove_point(PointsList *list, size_t index);

Point* points_list_get_point(PointsList *list, size_t index);

size_t points_list_get_count(PointsList *list);

void fprint_points_list(FILE *file, PointsList *list);

void print_points_list(PointsList *list);

void free_points_list(PointsList *list);

Stack* point_list_select_k_nearby(PointsList *list, Point *target, int k);

int select_class_bf(PointsList *list, Point *point, int k);

#endif /* _POINTS_LIST_H_ */