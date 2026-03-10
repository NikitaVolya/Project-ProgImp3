#include<stdlib.h>
#include<stdio.h>
#include<time.h>

typedef struct {
    float x;
    float y;
    int classe;
} Point;

typedef struct {
    Point * points;
    int nb_points;
    int nb_classes;
} Donnees;

#define dim 2
#define chemin "create/data.txt"

int charge_file(FILE * fichier, Donnees * donnees) {
    int n , c; 
    fichier = fopen(chemin,"r");
    if (fichier == NULL){
        fprintf(stderr,"probleme lors de l'ouverture du fichier data.txt.");
        exit(EXIT_FAILURE);
    }
    fscanf(fichier,"%d %d",&n,&c);
    donnees->nb_points = n;
    donnees->nb_classes = c;
    donnees->points = malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        fscanf(fichier,"%d %f %f",&donnees->points[i].classe,&donnees->points[i].x,&donnees->points[i].y);
    }
    fclose(fichier);
    return 0;
}

void free_donnees(Donnees * donnees) {
    free(donnees->points);
}

void affiche_donnees(Donnees * donnees) {
    for (int i = 0; i < donnees->nb_points; i++) {
        printf("Point %d: classe = %d, x = %f, y = %f\n", i, donnees->points[i].classe, donnees->points[i].x, donnees->points[i].y);
    }
}



int sauvegarde_donnees(Donnees * donnees) {
    FILE * fichier = fopen(chemin,"w");
    if (fichier == NULL){
        fprintf(stderr,"probleme lors de l'ouverture du fichier data.txt.");
        exit(EXIT_FAILURE);
    }
    fprintf(fichier,"%d %d\n",donnees->nb_points,donnees->nb_classes);
    for (int i = 0; i < donnees->nb_points; i++) {
        fprintf(fichier,"%d %f %f\n",donnees->points[i].classe,donnees->points[i].x,donnees->points[i].y);
    }
    fclose(fichier);
    return 0;
}

int add_point(Donnees * donnees, Point point) {
    donnees->points = realloc(donnees->points, (donnees->nb_points + 1) * sizeof(Point));
    donnees->points[donnees->nb_points] = point;
    donnees->nb_points++;
    return 0;
}
int remove_point(Donnees * donnees, int index) {
    for (int i = index; i < donnees->nb_points - 1; i++) {
        donnees->points[i] = donnees->points[i + 1];
    }
    donnees->nb_points--;
    return 0;
}