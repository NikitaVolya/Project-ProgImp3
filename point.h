#ifndef _POINT_H_
#define _POINT_H_

#include"vector.h"

typedef struct {
    int classe;
    Vector *position;
} Point;

Point* create_point(int classe, Vector *position);

int get_point_classe(Point *point);

float get_point_position(Point *point, size_t dimension);

void set_point_classe(Point *point, int classe);

void set_point_position(Point *point, size_t dimension, float value);

void free_point(Point *point);


#endif /* _POINT_H_ */