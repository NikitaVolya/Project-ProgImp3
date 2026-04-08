#include<stdlib.h>
#include<stdio.h>

#include"point.h"


int main() {
    Point *p, *p2;
    Vector *v;

    v = create_vector_with_values(3, 1.f, 2.f, 2.f);
    p = create_point(1, create_vector_with_values(3, 1.f, 2.f, 4.f));
    p2 = create_point(1, create_vector_with_values(3, 10.f, 3.f, 2.f));
    print_point(p);
    print_point(p2);

    move_point_to_position(p2, v);

    print_point(p);
    print_point(p2);

    printf("Distance p -> p2: %f\n", get_distance_to_point(p, p2));

    free_point(p);
    free_point(p2);
    free_vector(v);

    exit(EXIT_SUCCESS);
}