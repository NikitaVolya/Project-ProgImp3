
#include <stdlib.h>
#include <stdio.h>
#include "save.h"

int main(){
    FILE *file;
    PointsList *list;
    Point *new;

    file = fopen("data.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Cant open file\n");
        exit(EXIT_FAILURE);
    }

    if ((list = load_points_from_file(file)) == NULL) {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);

    new = create_point(0, create_vector_zero(5));
    printf("Class %d\n", select_class_bf(list, new, 10));

    free_points_list(list);
    

    exit(EXIT_SUCCESS);
}