#include "point.h"


typedef struct tree_kd {
    Point * P;
    struct tree_kd * right;
    struct tree_kd * left;
} tree_kd;

int is_empty_tree(tree_kd * t);

tree_kd * empty_tree();

tree_kd * create_tree_rec(Vector * V,int classe);

void add_tree(tree_kd * t,Vector * v,int classe);

void free_tree(tree_kd * t);