
#include <stdlib.h>
#include <stdio.h>
#include "save.h"
#include "tree_kd.h"
#include "interface.h"

void usage(char * m) {
    printf("usage: %s <data_file_directory>\n",m);
}

void test_tree(PointsList *list) {
    Stack *neibors;
    tree_kd *tree;
    Point *find_point;
    PointDistance *tmp_point;

    find_point = create_point(0, create_vector_with_values(2, -0.8f, 0.0f));

    tree = list_to_tree(list);

    if (is_empty_tree(tree))
        return;

    print_tree(tree);

    neibors = tree_select_k_nearby(tree, find_point, 4);

    while (!stack_is_empty(neibors)) {
        tmp_point = stack_pop(neibors);
        printf("%f <=> ", get_distance_to_point(tmp_point->point, find_point));
        print_point(tmp_point->point);
        free(tmp_point);
    }
    
    free_tree(tree);
    free_point(find_point);
}

void test_list(PointsList *list) {
    size_t i;
    Stack *res;
    Point *point, *target;
    double distance;

    printf("\n\n\n");

    target = create_point(0, create_vector_with_values(2, -0.8f, 0.0f));

    for (i = 0; i < points_list_get_count(list); i++) {
        point = points_list_get_point(list, i);

        distance = get_distance(get_point_vector(point), target->position);

        printf("%f <=>", distance);
        print_point(point);
    }

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

    /*

    test = interface_lancer();

    new = create_point(0, create_vector_zero(2));
    printf("Class %d\n", select_class_bf(list, new,k));

    
    printf("%d\n",test);
    */

    free_points_list(list);
    exit(EXIT_SUCCESS);
}