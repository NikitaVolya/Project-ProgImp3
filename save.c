#include "save.h"

Point* scan_point(FILE *file, size_t dimensions) {
    Point *res;
    size_t i;
    int class;
    float tmp;

    if ((res = create_point(0, create_vector(dimensions))) == NULL) {
        return NULL;
    }

    if (fscanf(file,"%d", &class) != 1){        
        fprintf(stderr,"Error while reading point class\n");
        free_point(res);
        return NULL;
    }

    set_point_classe(res, class);
    
    for (i = 0; i < dimensions; i++) {
        if (fscanf(file,"%f",&tmp) != 1){        
            fprintf(stderr, "Error while reading point position\n");
            free_point(res);
            return NULL;
        }
        set_point_position(res, i, tmp);
    }

    return res;
}

PointsList* load_points_from_file(FILE *file) {
    PointsList *res;
    Point *point;
    int number, classes, dimensions, i;

    if (file == NULL){
        fprintf(stderr,"Error file is NULL\n");
        return NULL;
    }

    if (fscanf(file,"%d %d %d\n", &number, &dimensions, &classes)!=3 ){
        fprintf(stderr,"probleme lors de la lecture du fichier data.txt code:1\n.");
        return NULL;
    };

    if ((res = create_points_list(number, classes, dimensions)) == NULL) {
        return NULL;
    }

    for (i = 0; i < number; i++) {
        point = scan_point(file, dimensions);
        if (get_point_classe(point) > res->nb_classes) {
            free_points_list(res);
            return NULL;
        }
        if (point != NULL) {
            points_list_add_point(res, point);
        }
    }

    return res;
}

int save_data_to_file(PointsList *list, FILE *file) {
    int res;
    size_t j, i;
    Point *point;

    res = 0;

    if (fprintf(file,"%ld %d %d\n", list->count, list->dimensions, list->nb_classes) == EOF) {
        res = 1;
    }
    
    for (i = 0; i < list->count && res == 0; i++) {
        point = list->points[i];
        if (fprintf(file, "%d ", get_point_classe(point)) == EOF) {
            res = 1;
        }
        for (j = 0; j < get_point_dimensions(point) && res == 0; j++) {
            if (fprintf(file, "%f ", get_point_position(point, j)) == EOF) {
                res = 1;
            }
        }
        fprintf(file,  "\n");
    }

    return res;
}
