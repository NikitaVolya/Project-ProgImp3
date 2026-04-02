#include<stdlib.h>
#include<stdio.h>

#include"vector.h"


int main() {
    Vector *a, *b;

    a = create_vector2_with_values(1.f, 2.f);
    b = create_vector2_with_values(1.f, 5.f);

    print_vector(a);
    print_vector(b);

    printf("Distance: %f\n", get_distance(a, b));

    exit(EXIT_SUCCESS);
}