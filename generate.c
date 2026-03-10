#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define dim 2
#define chemin "./data.txt"

void usage(char *m){
    printf("usage : %s <int nb_point> <int dimensions> <int nb_classe> \n",m);
}

FILE* create_file(){
    FILE * fichier;
    fichier = fopen(chemin,"w");
    if (fichier == NULL){
        fprintf(stderr,"probleme lors de l'ouverture du fichier data.txt.");
        exit(EXIT_FAILURE);
    }
    return fichier;
}

void generate_point(FILE * fichier,int classe){
    int c ;
    float x, y;
    c = (rand()%classe)+1 ;
    x = rand()/(float)RAND_MAX*dim-(dim/2.0) ;
    y = rand()/(float)RAND_MAX*dim-(dim/2.0) ;

    fprintf(fichier,"%d %f %f\n",c,x,y);
}


int generate_data(int n, int d, int c){
    int i; 
    FILE * fichier = NULL;


    fichier = create_file();

    fprintf(fichier,"%d %d %d\n",n,d,c);

    for (i=0;i<n;i++){
        generate_point(fichier,c);
    }
    
    exit(EXIT_SUCCESS);
}