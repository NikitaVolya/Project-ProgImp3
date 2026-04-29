
#include <stdlib.h>
#include <stdio.h>
#include "save.h"
#include "tree_kd.h"
#include "interface.h"

void usage(char * m) {
    printf("usage: %s <data_file_directory>\n",m);
}

int main(int argc,char ** argv){
    FILE *file;
    PointsList *list = NULL;

    int test;

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

    test = interface_lancer(list);

    printf("%d",test);

    free_points_list(list);
    exit(EXIT_SUCCESS);
}