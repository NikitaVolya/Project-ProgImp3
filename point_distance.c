#include"point_distance.h"


void check_point_distance_on_null(const char *fname, PointDistance *point_distance) {
    if (point_distance == NULL) {
        fprintf(stderr, "%s interrupted\nPointDistance is NULL\n", fname);
        exit(EXIT_FAILURE);
    }
}

PointDistance* create_point_distance(Point *point, Point* target) {
    PointDistance* res;

    check_point_on_null("create_point_distance", point);
    check_point_on_null("create_point_distance", target);

    if ((res = (PointDistance*) malloc(sizeof(PointDistance))) == NULL) {
        return NULL;
    }
    res->point = point;
    res->distance = get_distance_to_point(point, target);
    return res;
}


Point* get_point_distance_point(PointDistance *point_distance) {

    check_point_distance_on_null("get_point_distance_point", point_distance);

    return point_distance->point;
}

double get_point_distance_value(PointDistance *point_distance) {

    check_point_distance_on_null("get_point_distance_value", point_distance);

    return point_distance->distance;
}