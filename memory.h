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

int charge_file(FILE * fichier, Donnees * donnees);

void free_donnees(Donnees * donnees);

void affiche_donnees(Donnees * donnees);

int sauvegarde_donnees(Donnees * donnees);

int add_point(Donnees * donnees, Point point);

int remove_point(Donnees * donnees, int index) ;