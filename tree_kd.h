#include "points_list.h"

typedef struct tree_kd {
    Point * P;
    struct tree_kd * right;
    struct tree_kd * left;
} tree_kd;

int is_empty_tree(tree_kd *t);

tree_kd * empty_tree();

tree_kd * create_tree(Vector *V, int classe);

void add_tree(tree_kd *t, Vector *v, int classe);

Vector* nearby_area_point(tree_kd *t, Vector *p); 

void free_tree(tree_kd *t);