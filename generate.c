#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define dim 2
#define path "./data.txt"


FILE* create_file(){
    FILE * file;
    file = fopen(path,"w");
    if (file == NULL){
        fprintf(stderr,"probleme lors de l'ouverture du fichier data.txt.");
        exit(EXIT_FAILURE);
    }
    return file;
}

void generate_point(FILE * file,int classe){
    int c ;
    float x, y;
    c = (rand()%classe)+1 ;
    x = rand()/(float)RAND_MAX*dim-(dim/2.0) ;
    y = rand()/(float)RAND_MAX*dim-(dim/2.0) ;

    fprintf(file,"%d %f %f\n",c,x,y);
}


int generate_data(int n, int d, int c){
    int i; 
    FILE * file = NULL;


    file = create_file();

    fprintf(file,"%d %d %d\n",n,d,c);

    for (i=0;i<n;i++){
        generate_point(file,c);
    }
    
    exit(EXIT_SUCCESS);
}