
#include <stdlib.h>
#include <stdio.h>
#include "save.h"
#include "tree_kd.h"
#include "interface.h"

void usage(char * m){
    printf("usage: %s <data_file_directory>\n",m);
}

void test_tree(PointsList *list) {
    size_t i;
    tree_kd *tree;
    Point *point;
    Vector *vector;
    double distance;

    tree = empty_tree();
    vector = create_vector_with_values(2, 0.5f, 0.5f);

    for (i = 0; i < points_list_get_count(list); i++) {
        point = points_list_get_point(list, i);

        distance = get_distance(get_point_vector(point), vector);

        printf("%f <=>", distance);
        print_point(point);

        if (is_empty_tree(tree)) {
            tree = create_tree(
                get_point_vector(point),
                get_point_classe(point)
            );
        } else {
            add_tree(
                tree,
                get_point_vector(point),
                get_point_classe(point)
            );
        }
    }

    print_vector(nearby_area_point(tree, vector));

    if (is_empty_tree(tree))
        return;
    
    free_tree(tree);
    free_vector(vector);
}

void test_list(PointsList *list) {
    size_t i;
    Point *point, *target;
    double distance;

    printf("\n\n\n");

    target = create_point(0, create_vector_with_values(2, 0.5f, 0.5f));

    for (i = 0; i < points_list_get_count(list); i++) {
        point = points_list_get_point(list, i);

        distance = get_distance(get_point_vector(point), target->position);

        printf("%f <=>", distance);
        print_point(point);
    }

    select_class_bf(list, target, 3);
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

    /*

    test = interface_lancer();

    new = create_point(0, create_vector_zero(2));
    printf("Class %d\n", select_class_bf(list, new,k));

    
    printf("%d\n",test);
    */

    free_points_list(list);
    exit(EXIT_SUCCESS);
}