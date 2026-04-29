#include"point.h"

void check_point_on_null(const char *fname, Point *point) {
    if (point == NULL) {
        fprintf(stderr, "%s interrupted\nPoint is NULL\n", fname);
        exit(EXIT_FAILURE);
    }
}

Point* create_point(int classe, Vector *position) {
    Point *res;

    if (position == NULL) {
        fprintf(stderr, "Error while creating Point. position is NULL\n");
        return NULL;
    }

    /* memory allocation */
    if ((res = (Point*) malloc(sizeof(Point))) == NULL) {
        fprintf(stderr, "create_point interrupted\nError while memory allocation\n");
        exit(EXIT_FAILURE);
    }

    /* init values */
    res->classe = classe;
    res->position = position;

    return res;
}

Point* create_point_copy(Point *source) {
    /* data check */
    check_point_on_null("create_point_copy", source);

    return create_point(source->classe, create_vector_copy(source->position));
}

int get_point_classe(Point *point) {
    /* data check */
    check_point_on_null("get_point_classe", point);

    return point->classe;
}

void set_point_classe(Point *point, int classe) {
    /* data check */
    check_point_on_null("set_point_classe", point);

    point->classe = classe;
}

void set_point_position(Point *point, size_t dimension, float value) {
    /* data check */
    check_point_on_null("set_point_position", point);

    set_vector_value(point->position, dimension, value);
}

float get_point_position(Point *point, size_t dimension) {
    /* data check */
    check_point_on_null("get_point_position", point);

    return get_vector_value(point->position, dimension);
}


Vector* get_point_vector(Point *point) {
    /* data check */
    check_point_on_null("get_point_vector", point);

    return point->position;
}

size_t get_point_dimensions(Point *point) {
    /* data check */
    check_point_on_null("get_point_dimensions_number", point);

    return get_vector_dimensions(point->position);
}

void move_point_to_position(Point *point, Vector *position) {
    size_t i, d;

    /* data check */
    check_point_on_null("move_point_to_position", point);

    /* check on dimensions of points */
    if (get_vector_dimensions(point->position) != get_vector_dimensions(position)) {
        fprintf(stderr, "Error move_point_to_position\nnew position must have same dimensions number\n");
        exit(EXIT_FAILURE);
    }

    /* copy coords from vector position to point->position */
    d = get_vector_dimensions(point->position);
    for (i = 0; i < d; i++) {
        set_vector_value(point->position, i, get_vector_value(position, i));
    }
}

double get_distance_to_point(Point *source, Point *destination) {

    /* check input data */
    check_point_on_null("get_distance_to_point : source", source);
    check_point_on_null("get_distance_to_point : destination", destination);

    return get_distance(source->position, destination->position);
}

void fprint_point(FILE *out, Point *point) {
    if (point == NULL) {
        /* NULL output */
        fprintf(out, "NULL\n");
    } else {
        fprintf(out, "| Point : classe %d \t", point->classe);
        fprint_vector(out, point->position);
    }
}

void print_point(Point *point) {
    fprint_point(stdout, point);
}

void free_point(void *value) {
    Point *point = (Point*) value;

    check_point_on_null("free_point", point);

    free_vector(point->position);
    free(point);
}