#include "save.h"

void charge_file( Data * data) {
    FILE * file ;
    int n, c, i, d, j; 
    file = fopen(path,"r");
    if (file == NULL){
        fprintf(stderr,"probleme lors de l'ouverture du fichier data.txt. code:0\n");
        exit(EXIT_FAILURE);
    }
    if (fscanf(file,"%d %d %d\n",&n,&d,&c)!=3 ){
        fprintf(stderr,"probleme lors de la lecture du fichier data.txt code:1\n.");
        exit(EXIT_FAILURE);
    };
    data->nb_points = n;
    data->nb_classes = c;
    data->dimension = d;
    data->points = malloc(n * sizeof(Point));
    for (i = 0; i < n; i++) {
        data->points[i].pos = malloc((size_t)d * sizeof(float));
        if (fscanf(file,"%d",&data->points[i].classe)!=1){        
            fprintf(stderr,"probleme lors de la lecture du fichier data.txt code:2. \n");
            exit(EXIT_FAILURE);
        }
        for (j=0;j<d;j++){
            if (fscanf(file,"%f",&data->points[i].pos[j])!=1){        
                fprintf(stderr,"probleme lors de la lecture du fichier data.txt code:3.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(file);
}
 



void free_data(Data * data) {
    int i;
    if (data->points == NULL) return;
    for (i = 0; i < data->nb_points; i++)
        free(data->points[i].pos);
    free(data->points);
    data->points = NULL;
    data->nb_points = 0;
}

void display_data(Data data) {
    int i,j;
    for (i = 0; i < data.nb_points; i++) {
        printf("Point %d: classe = %d", i, data.points[i].classe);
        for (j = 0; j < data.dimension; j++) {
            printf(", %f",data.points[i].pos[j]);
        }
        printf("\n");
    }
    
}



int save_data(Data * data) {
    int j,k;
    FILE * file = fopen(path,"w");
    if (file == NULL){
        fprintf(stderr,"probleme lors de l'ouverture du fichier data.txt. code:4");
        exit(EXIT_FAILURE);
    }
    fprintf(file,"%d %d %d\n",data->nb_points,data->dimension,data->nb_classes);
    for (j = 0; j < data->nb_points; j++) {
        fprintf(file,"%d ", data->points[j].classe);
        for (k = 0; k < data->dimension; k++) {
            fprintf(file,"%f ",data->points[j].pos[k]);
        }
        fprintf(file,"\n");
    }
    fclose(file);
    return 0;
}

int add_point(Data * data, Point point) {
    data->points = realloc(data->points, (data->nb_points + 1) * sizeof(Point));
    data->points[data->nb_points] = point;
    data->nb_points++;
    return 0;
}
int remove_point(Data * data, int index) {
    int i;
    free(data->points[index].pos);
    for (i = index; i < data->nb_points - 1; i++) {
        data->points[i] = data->points[i + 1];
    }
    data->nb_points--;
    data->points = realloc(data->points, (size_t)data->nb_points * sizeof(Point));
    return 0;
}
