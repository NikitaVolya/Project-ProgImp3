
#include <stdlib.h>
#include <stdio.h>
#include "save.h"

int main(){
    FILE *file;
    PointsList *list;

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

    print_points_list(list);
    points_list_remove_point(list, 1);
    print_points_list(list);


    if ((file = fopen("output.txt", "w")) == NULL) {
        fprintf(stderr, "Cant open file\n");
        exit(EXIT_FAILURE);
    }

    save_data_to_file(list, file);

    fclose(file);

    free_points_list(list);
    

    exit(EXIT_SUCCESS);
}