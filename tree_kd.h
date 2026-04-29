#include "points_list.h"

typedef struct tree_kd {
    Point * P;
    struct tree_kd * right;
    struct tree_kd * left;
} tree_kd;

typedef struct {
    Vector *p_min, *p_max;
    tree_kd *tree;
    size_t dimension;
} Zone;

int is_empty_tree(tree_kd *t);

tree_kd * empty_tree();

tree_kd * create_tree(Vector *V, int classe);

tree_kd* list_to_tree(PointsList* list);

void add_tree(tree_kd *t, Vector *v, int classe);

Point* nearby_zone_point(Zone *zone, Point *p); 

int check_point_in_zone(Zone *zone, Point *p);

PointsList* tree_kd_select_k_nearby(tree_kd *tree, Point *p, int target);

void free_tree(tree_kd *t);

Zone* create_zone(tree_kd *tree, Vector *lt, Vector *rd, size_t dimension);

Zone* create_base_zone(tree_kd *tree);

Zone* get_left_zone(Zone *zone);

Zone* get_right_zone(Zone *zone);

Stack* tree_select_k_nearby(tree_kd *tree, Point *target, int k);

void free_zone(Zone *zone);