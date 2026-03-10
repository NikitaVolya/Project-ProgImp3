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

void generate_point(FILE * fichier,int class){
    int c ;
    float x, y;
    c = (rand()%class)+1 ;
    x = rand()/(float)RAND_MAX*dim-(dim/2.0) ;
    y = rand()/(float)RAND_MAX*dim-(dim/2.0) ;

    fprintf(fichier,"%d %f %f\n",c,x,y);
}

int main(int argc,char ** argv) {
    int i ,n  ,d ,c; 
    FILE * fichier = NULL;



    if (argc != 4){
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    fichier = create_file();

    n = atoi(argv[1]);
    d = atoi(argv[2]);
    c = atoi(argv[3]);

    fprintf(fichier,"%d %d %d\n",n,d,c);

    for (i=0;i<n;i++){
        generate_point(fichier,c);
    }
    
    exit(EXIT_SUCCESS);
}