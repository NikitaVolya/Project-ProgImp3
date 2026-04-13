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

tree_kd * create_tree_rec(Vector * V,int classe){
    tree_kd * t;
    t = (tree_kd *) malloc(sizeof(tree_kd));
    t->P = create_point(classe, V);
    t->left = empty_tree();
    t->right = empty_tree();
    return t;
}

void add_tree(tree_kd * t,Vector * v,int classe){
    size_t index;
    tree_kd * new,* courrant;
    index = 0 ;
    new = create_tree_rec(v,classe);
    courrant = t;
    while (courrant->left != NULL && courrant->right != NULL) {
        if (courrant->P->position->values[index%courrant->P->position->dimensions] > v->values[index%courrant->P->position->dimensions]){
            courrant = courrant->left;
        }
        else {
            courrant = courrant->right;
        }
        index++;
    }

    if (courrant->P->position->values[index%courrant->P->position->dimensions] > v->values[index%courrant->P->position->dimensions]){
        courrant->left = new;
    }
    else {
        courrant->right = new;
    }
}

void free_tree(tree_kd * t){
    if (t->left != NULL && t->right != NULL){
        fprintf(stderr,"erreur lors de la liberation vous devez liberer les enfant avant le parent.\n ");
        exit(EXIT_FAILURE);
    }
    free(t);
}