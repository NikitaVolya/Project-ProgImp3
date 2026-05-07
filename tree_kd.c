#include "tree_kd.h"
#include "point.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int is_empty_tree(tree_kd * t){
    int retour = 0 ;
    if(t == NULL){
        retour = 1;
    }
    return retour;
}

tree_kd * empty_tree(){
    return NULL;
}

tree_kd * create_tree(Vector * V,int classe){
    tree_kd * t;
    t = (tree_kd *) malloc(sizeof(tree_kd));
    t->P = create_point(classe, create_vector_copy(V));
    t->left = empty_tree();
    t->right = empty_tree();
    return t;
}

tree_kd* list_to_tree(PointsList* list) {
    size_t i;
    tree_kd *tree;
    Point *point;

    tree = empty_tree();

    for (i = 0; i < points_list_get_count(list); i++) {
        point = points_list_get_point(list, i);

        if (is_empty_tree(tree)) {
            tree = create_tree(
                get_point_vector(point),
                get_point_classe(point)
            );
        } else {
            add_tree(
                tree,
                get_point_vector(point),
                get_point_classe(point)
            );
        }
    }

    return tree;
}

void add_tree(tree_kd * t,Vector * v,int classe){
    size_t profondeur, dimensions;
    int cycle;

    tree_kd * new,* courrant;
    profondeur = 0 ;
    new = create_tree(v,classe);

    courrant = t;
    cycle = 1;
    dimensions = get_point_dimensions(t->P);

    if (dimensions != get_vector_dimensions(v)) {
        fprintf(stderr, "add_tree interrupted\nVectors have different dimensions\n");
        exit(EXIT_FAILURE);
    }

    while (cycle) {
        if (get_vector_value(v, profondeur) < get_point_position(courrant->P, profondeur)) {
            if (is_empty_tree(courrant->left)) {
                cycle = 0;
                courrant->left = new;
            } else {
                courrant = courrant->left;
            }
        }
        else {
            if (is_empty_tree(courrant->right)) {
                cycle = 0;
                courrant->right = new;
            } else {
                courrant = courrant->right;
            }
        }

        profondeur = (profondeur + 1) % dimensions;
    }
}

void print_tree(tree_kd *t, size_t tab) {
    size_t i;

    if (!is_empty_tree(t)) {
        for (i = 0; i < tab; i++)
            printf("     -");
        printf("=> ");
        print_point(t->P);
        print_tree(t->left, tab + 1);
        print_tree(t->right, tab + 1);
    }
}

void free_tree(tree_kd * t){
    if (!is_empty_tree(t)) {
        free_tree(t->left);
        free_tree(t->right);
        free_point(t->P);
        free(t);
    }
}

Zone* create_zone(tree_kd *tree, Vector *lt, Vector *rd, size_t dimension) {
    Zone *res;

    if ((res = (Zone*) malloc(sizeof(Zone))) == NULL) {
        fprintf(stderr, "Error while memory allocation");
        exit(EXIT_FAILURE);
    }

    res->p_min = lt;
    res->p_max = rd;
    res->dimension = dimension;
    res->tree = tree;
    
    return res;
}

Zone* create_base_zone(tree_kd *tree) {
    size_t dimensions, i;
    Vector *p_min, *p_max;

    if (tree == NULL) {
        fprintf(stderr, "Error in create_base_zone. tree is NULL\n");
        exit(EXIT_FAILURE);
    }

    dimensions = get_point_dimensions(tree->P);
    p_min = create_vector(dimensions);
    p_max = create_vector(dimensions);

    for (i = 0; i < dimensions; i++) {
        set_vector_value(p_min, i, -1.f);
        set_vector_value(p_max, i, 1.f);
    }

    return create_zone(tree, p_min,p_max, 0);
}

Zone* get_left_zone(Zone *zone) {
    size_t next_dim, dimensions;
    Vector *new_p_min, *new_p_max;

    if (zone->tree->left == NULL)
        return NULL;

    dimensions = get_point_dimensions(zone->tree->P);

    next_dim = (zone->dimension + 1) % dimensions;
    new_p_min = create_vector_copy(zone->p_min);
    new_p_max = create_vector_copy(zone->p_max);

    set_vector_value(new_p_max, zone->dimension, get_point_position(zone->tree->P, zone->dimension));

    return create_zone(zone->tree->left, new_p_min, new_p_max, next_dim);
}

Zone* get_right_zone(Zone *zone) {
    size_t next_dim, dimensions;
    Vector *new_p_min, *new_p_max;
    
    if (zone->tree->right == NULL)
        return NULL;

    dimensions = get_point_dimensions(zone->tree->P);

    next_dim = (zone->dimension + 1) % dimensions;
    new_p_min = create_vector_copy(zone->p_min);
    new_p_max = create_vector_copy(zone->p_max);

    set_vector_value(new_p_min, zone->dimension, get_point_position(zone->tree->P, zone->dimension));

    return create_zone(zone->tree->right, new_p_min, new_p_max, next_dim);
}


Point* nearby_zone_point(Zone *zone, Point *p) {
    Vector *res, *p_v;
    size_t dimensions, i;
    float x, x_min, x_max;

    p_v = get_point_vector(p);
    dimensions = get_vector_dimensions(p_v);
    res = create_vector(dimensions);

    for (i = 0; i < dimensions; i++) {
        x = get_vector_value(p_v, i);
        x_min = get_vector_value(zone->p_min, i);
        x_max = get_vector_value(zone->p_max, i);
        if (x < x_min)
            set_vector_value(res, i, x_min);
        else if (x > x_max)
            set_vector_value(res, i, x_max);
        else
            set_vector_value(res, i, x);
    }

    return create_point(0, res);
}


int check_point_in_zone(Zone *zone, Point *p) {
    return check_vector_ge(zone->p_min, get_point_vector(p)) &&
           check_vector_le(zone->p_max, get_point_vector(p));
}

void free_zone(Zone *zone) {
    free_vector(zone->p_min);
    free_vector(zone->p_max);
    free(zone);
}

/**
 * @brief Recursive K-nearest neighbors search in KD-tree.
 *
 * Traverses the tree using bounding boxes and pruning strategy.
 *
 * @param[in] zone Current search zone.
 * @param[in,out] list Ordered list of nearest points.
 * @param[in] target Query point.
 */
void tree_select_k_nearby_rec(Zone *zone, OrderedPointsList *list, Point *target) {
    Zone *left, *right, *first, *second;
    Point *p, *left_p, *right_p;

    if (zone == NULL)
        return;

    left = get_left_zone(zone);
    right = get_right_zone(zone);

    p = zone->tree->P;
    
    ordered_points_list_add_point(list, p, target);

    if (left == NULL) {
        first = right;
        second = left;
    } else if (right == NULL) {
        first = left;
        second = right;
    } else if (check_point_in_zone(left, target)) {
        first = left;
        second = right;
    } else if (check_point_in_zone(right, target)) {
        first = right;
        second = left;
    } else{
        left_p = nearby_zone_point(left, target);
        right_p = nearby_zone_point(right, target);

        if (get_distance_to_point(target, left_p) < get_distance_to_point(target, right_p)) {
            first = left;
            second = right;
        } else {
            first = right;
            second = left;
        }

        free_point(left_p);
        free_point(right_p);
    }

    tree_select_k_nearby_rec(first, list, target);

    
    if (second != NULL) {
        left_p = get_ordered_points_first_point(list)->point;
        right_p = nearby_zone_point(second, target);
        
        if (left_p == NULL || get_distance_to_point(right_p, target) <= get_distance_to_point(left_p, target)) {
            tree_select_k_nearby_rec(second, list, target);
        }

        free_point(right_p);
    }

    if (left != NULL)
        free_zone(left);
    if (right != NULL)
        free_zone(right);
}

Stack* tree_select_k_nearby(tree_kd *tree, Point *target, int k) {
    Stack *res;
    Zone *base_zone;
    OrderedPointsList *list;

    base_zone = create_base_zone(tree);
    list = create_ordered_point_list(k);
    
    tree_select_k_nearby_rec(base_zone, list, target);

    res = extract_points(list);
    free_ordered_points_list(list);

    free_zone(base_zone);

    return res;
}

int select_tree_class(tree_kd *tree, Point *target, int k, int nb_classes) {
    Stack *best_stack;
    int best_class;

    if (k < 1 || tree == NULL || target == NULL)
        return -1;

    best_stack = tree_select_k_nearby(tree, target, k);
    best_class = extract_majority_class_from_stack(best_stack, nb_classes);

    free_stack(best_stack);

    set_point_classe(target, best_class);

    return best_class;  
}
