#include<stdlib.h>
#include<stdio.h>
#include<time.h>


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
    fprintf(stdout,"%d %d %d\n",n,d,c);

    for (i=0;i<n;i++){
        generate_point(fichier,c,d);
    }
    
    exit(EXIT_SUCCESS);
}