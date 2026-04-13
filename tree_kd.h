#include "vector.h"

typedef struct tree_kd {
    Vector * value;
    struct tree_kd * right;
    struct tree_kd * left;
} tree_kd;

int is_empty_tree(tree_kd * t);

tree_kd * empty_tree();

tree_kd * create_tree_rec(Vector * V);

void add_tree(tree_kd * t,Vector * v);

void free_tree(tree_kd * t);