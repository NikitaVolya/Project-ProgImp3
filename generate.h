#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define dim 2
#define chemin "./data.txt"

void usage(char *m);

FILE* create_file();

void generate_point(FILE * fichier,int classe);


int generate_data(int n, int d, int c);