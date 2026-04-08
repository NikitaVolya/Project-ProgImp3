#include<stdlib.h>
#include<stdio.h>
#include<time.h>

void usage(char *m){
    printf("usage : %s <int nb_point> <int dimensions> <int nb_classe> \n",m);
}

void generate_point(FILE * fichier, int class, int dim){
    int c ,i;
    float x;

    c = (rand()%class)+1 ;
    fprintf(fichier,"%d ",c);
    for (i=0;i<dim;i++){
        x = rand()/(double)RAND_MAX*2-1 ;
        fprintf(fichier,"%lf ",x);
    }
    fprintf(fichier,"\n");
}


int main(int argc,char ** argv) {
    int i, n, d, c; 

    if (argc != 4) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    n = atoi(argv[1]);
    d = atoi(argv[2]);
    c = atoi(argv[3]);

    if (n < 0 || d <= 0 || c <= 0){
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout,"%d %d %d\n",n,d,c);

    for (i=0;i<n;i++){
        generate_point(stdout, c, d);
    }
    
    exit(EXIT_SUCCESS);
}