
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "save.h"
#include "tree_kd.h"
#include "interface.h"
#include "time.h"

void usage(char * m) {
    printf("usage: %s -i <data_file_directory>\n",m);
}

void test_tree(tree_kd *tree, int k, int nb_classes) {
    Point *find_point;

    find_point = create_point(0, create_vector_zero(get_point_dimensions(tree->P)));

    select_tree_class(tree, find_point, k, nb_classes);

    free_point(find_point);
}

void test_list(PointsList *list, int k) {
    Point *target;


    target = create_point(0, create_vector_zero(list->dimensions));

    select_class_bf(list, target, k);
}

int main(int argc,char ** argv) {
    FILE *file, *save_file;
    PointsList *list = NULL;
    tree_kd *tree;
    struct timespec debut,fin;
    int test,k;
    double sec_list, sec_tree;

    if (argc != 5 && argc != 3){
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[2], "r");
    if (file == NULL) {
        fprintf(stderr, "Cant open file\n");
        exit(EXIT_FAILURE);
    }

    if ((list = load_points_from_file(file)) == NULL) {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);

    if (strcmp(argv[1],"-t") == 0) {
        char *mode = argv[3];
        k = atoi(argv[4]);

        tree = list_to_tree(list);

        clock_gettime(CLOCK_REALTIME, &debut);
        test_tree(tree, k, list->nb_classes);
        clock_gettime(CLOCK_REALTIME, &fin);
        sec_tree = (fin.tv_sec - debut.tv_sec) + (fin.tv_nsec - debut.tv_nsec) / 1000000000.0;

        free_tree(tree);

        clock_gettime(CLOCK_REALTIME, &debut);
        test_list(list, k);
        clock_gettime(CLOCK_REALTIME, &fin);
        sec_list = (fin.tv_sec - debut.tv_sec) + (fin.tv_nsec - debut.tv_nsec) / 1000000000.0;

        long var;
        if (strcmp(mode, "k") == 0)
            var = k;
        else if (strcmp(mode, "d") == 0)
            var = (long)list->dimensions;
        else if (strcmp(mode, "p") == 0)
            var = (long)list->count;
        else {
            fprintf(stderr, "Mode inconnu : %s (utiliser k, d ou p)\n", mode);
            free_points_list(list);
            exit(EXIT_FAILURE);
        }

        save_file = fopen("save_tree.txt", "a");
        fprintf(save_file, "%.6f %ld\n", sec_tree, var);
        fclose(save_file);

        save_file = fopen("save_list.txt", "a");
        fprintf(save_file, "%.6f %ld\n", sec_list, var);
        fclose(save_file);
    }
    else if (strcmp(argv[1], "-i") == 0) {
        test = interface_lancer(list);
        printf("%d",test);
    }

    free_points_list(list);
    exit(EXIT_SUCCESS);
}