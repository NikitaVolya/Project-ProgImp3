#include"point.h"

void check_point_on_null(const char *fname, Point *point) {
    if (point == NULL) {
        fprintf(stderr, "%s interrupted\nPoint is NULL\n", fname);
        exit(EXIT_FAILURE);
    }
}

Point* create_point(int classe, Vector *position) {
    Point *res;

    if ((res = (Point*) malloc(sizeof(Point))) == NULL) {
        fprintf(stderr, "create_point interrupted\nError while memory allocation\n");
        exit(EXIT_FAILURE);
    }

    res->classe = classe;
    res->position = create_vector_copy(position);

    return res;
}

int get_point_classe(Point *point) {
    check_on_null("get_point_classe", point);

    return point->classe;
}

float get_point_position(Point *point, size_t dimension) {
    check_on_null("get_point_position", point);
    
    return get_vector_value(point->position, dimension);
}

void set_point_classe(Point *point, int classe) {
    check_on_null("set_point_classe", point);

    point->classe = classe;
}

void set_point_position(Point *point, size_t dimension, float value);

void free_point(Point *point);