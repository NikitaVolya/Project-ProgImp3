#include "tree_kd.h"
#include "point.h"
#include <stddef.h>
#include<stdlib.h>
#include<stdio.h>

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

void add_tree(tree_kd * t,Vector * v,int classe){
    size_t profondeur;
    int cycle;

    tree_kd * new,* courrant;
    profondeur = 0 ;
    new = create_tree(v,classe);

    courrant = t;
    cycle = 1;

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

        profondeur = (profondeur + 1) % get_point_dimensions(courrant->P);
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

Vector* nearby_area_point(tree_kd *t, Point *p) {
    Vector *res, *cur_p, *p_v;
    tree_kd *current;
    size_t index;
    double dist, cur_dist;

    current = t;
    index = 0;

    res = NULL;
    dist = 0;

    p_v = get_point_vector(p);

    print_tree(t, 0);

    while (current != NULL) {
        cur_p = get_point_vector(current->P);

        printf("iteration: ");
        printf("dist %f | best %f  =", cur_dist, dist);
        print_vector(cur_p);

        cur_dist = get_distance(cur_p, p_v);
        if (res == NULL || cur_dist < dist) {
            dist = cur_dist;
            res = cur_p;
        }

        if (get_vector_value(p_v, index) < get_vector_value(cur_p, index)) {
            current = current->left;
        } else {
            current = current->right;
        }

        index = (index + 1) % get_vector_dimensions(cur_p);
    }

    return res;
}

int find_point_in_area(tree_kd *t, Point *p) {

    Vector *cur_p, *p_v;
    tree_kd *current;
    size_t index;
    int res = 0;

    current = t;
    index = 0;

    p_v = get_point_vector(p);

    print_tree(t, 0);

    while (current != NULL && res == 0) {
        cur_p = get_point_vector(current->P);

        if (check_vector_eq(cur_p, p_v)) {
            res = 1;
        } else {
            if (get_vector_value(p_v, index) < get_vector_value(cur_p, index)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        index = (index + 1) % get_vector_dimensions(cur_p);
    }

    return res;
}

void free_tree(tree_kd * t){
    if (!is_empty_tree(t)) {
        free_tree(t->left);
        free_tree(t->right);
        free_point(t->P);
    }
}