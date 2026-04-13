#include<stdlib.h>
#include<stdio.h>
#include<time.h>


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

void generate_point(FILE * fichier,int class,int dim){
    int c ,i;
    float x;

    c = (rand()%class)+1 ;
    fprintf(fichier,"%d ",c);
    fprintf(stdout,"%d ",c);
    for (i=0;i<dim;i++){
        x = rand()/(double)RAND_MAX*2-1 ;
        fprintf(fichier,"%lf ",x);
        fprintf(stdout,"%lf ",x);
    }
    fprintf(fichier,"\n");
    fprintf(stdout,"\n");
}

int generate_data(int n, int d, int c){
    int i; 
    FILE * file = NULL;


    file = create_file();

    fprintf(file,"%d %d %d\n",n,d,c);

    for (i=0;i<n;i++){
        generate_point(file,c,d);
    }
    
    exit(EXIT_SUCCESS);
}