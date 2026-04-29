
#include <stdlib.h>
#include <stdio.h>
#include "save.h"
#include "tree_kd.h"
#include "interface.h"

void usage(char * m) {
    printf("usage: %s <data_file_directory>\n",m);
}

void test_tree(PointsList *list) {
    Point *find_point;

    find_point = create_point(0, create_vector_zero(list->dimensions));

    select_tree_class(list, find_point, 4);
    
    free_point(find_point);
}

void test_list(PointsList *list) {
    Point *point, *target;
    double distance;
    size_t i;

    printf("\n\n\n");

    target = create_point(0, create_vector_zero(list->dimensions));

    select_class_bf(list, target, 4);
}

int main(int argc,char ** argv){
    FILE *file;
    PointsList *list;
    Point *new;
    int k,test;
    k = 10 ;
    if (argc !=2 ){
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Cant open file\n");
        exit(EXIT_FAILURE);
    }

    if ((list = load_points_from_file(file)) == NULL) {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);

    test_tree(list);

    test_list(list);

    free_points_list(list);
    exit(EXIT_SUCCESS);
}