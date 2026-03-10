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
} Data;

#define dim 2
#define path "create/data.txt"

void charge_file(FILE * file, Data * data) {
    int n , c; 
    file = fopen(path,"r");
    if (file == NULL){
        fprintf(stderr,"probleme lors de l'ouverture du fichier data.txt.");
        exit(EXIT_FAILURE);
    }
    fscanf(file,"%d %d",&n,&c);
    data->nb_points = n;
    data->nb_classes = c;
    data->points = malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        fscanf(file,"%d %f %f",&data->points[i].classe,&data->points[i].x,&data->points[i].y);
    }
    fclose(file);

}

void free_data(Data * data) {
    free(data->points);
}

void display_data(Data * data) {
    for (int i = 0; i < data->nb_points; i++) {
        printf("Point %d: classe = %d, x = %f, y = %f\n", i, data->points[i].classe, data->points[i].x, data->points[i].y);
    }
}



void save_data(Data * data) {
    FILE * file = fopen(path,"w");
    if (file == NULL){
        fprintf(stderr,"probleme lors de l'ouverture du fichier data.txt.");
        exit(EXIT_FAILURE);
    }
    if (fprintf(file,"%d %d\n",data->nb_points,data->nb_classes) < 0){
        fprintf(stderr,"probleme lors de l'ecriture du fichier data.txt.");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < data->nb_points; i++) {
        if (fprintf(file,"%d %f %f\n",data->points[i].classe,data->points[i].x,data->points[i].y) < 0){
            fprintf(stderr,"probleme lors de l'ecriture du fichier data.txt.");
            exit(EXIT_FAILURE);
        }
    }
    fclose(file);

}

void add_point(Data * data, Point point) {
    data->points = realloc(data->points, (data->nb_points + 1) * sizeof(Point));
    data->points[data->nb_points] = point;
    data->nb_points++;
}
void remove_point(Data * data, int index) {
    for (int i = index; i < data->nb_points - 1; i++) {
        data->points[i] = data->points[i + 1];
    }
    data->nb_points--;
}