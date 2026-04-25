
#include <stdlib.h>
#include <stdio.h>
#include "save.h"
#include "interface.h"

void usage(char * m){
    printf("usage: %s <data_file_directory>",m);
}

int main(int argc,char ** argv){
    FILE *file;
    PointsList *list = NULL;
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

    test = interface_lancer(list,argv[1]);

    new = create_point(0, create_vector_zero(get_point_dimensions (points_list_get_point(list,0))));
    printf("Class %d\n", select_class_bf(list, new,k));

    free_points_list(list);
    
    printf("%d\n",test);
    exit(EXIT_SUCCESS);
}