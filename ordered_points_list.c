#include"ordered_points_list.h"


OrderedPointsList* create_ordered_point_list(size_t maxsize) {
    OrderedPointsList* res;

    if ((res = (OrderedPointsList*) malloc(sizeof(OrderedPointsList))) == NULL) {
        return NULL;
    }
    res->maxsize = maxsize;
    res->best_stack = create_stack();
    res->tmp_stack = create_stack();

    return res;
}

void free_ordered_points_list(OrderedPointsList* list) {
    free_stack(list->best_stack);
    free_stack(list->tmp_stack);
    free(list);
}

OrderedPointsList* ordered_points_list_add_point(OrderedPointsList* list, Point *point, Point *target) {
    PointDistance *pointDist, *tmp;
    
    pointDist = create_point_distance(point, target);

    /* transfer all points with grater distance than point to tmp_stack from best_stack */
    while (!stack_is_empty(list->best_stack) && 
        ((PointDistance*) stack_value(list->best_stack))->distance > pointDist->distance) {
        tmp = stack_pop(list->best_stack);
        stack_push(list->tmp_stack, tmp);
    }

    /* add pointDist to best_stack if enough place or free them */
    if (get_stack_size(list->best_stack) < list->maxsize) {
        stack_push(list->best_stack, pointDist);
    } else {
        free(pointDist);
    }

    /* add points from tmp_stack to best_stack if enough place */
    while (!stack_is_empty(list->tmp_stack) && 
            get_stack_size(list->best_stack) < list->maxsize) {
        stack_push(list->best_stack, stack_pop(list->tmp_stack));
    }

    /* clear tmp_stack */
    stack_clear(list->tmp_stack);

    return list;
}

Stack* extract_points(OrderedPointsList *list) {
    Stack *res;

    res = list->best_stack;
    list->best_stack = create_stack();

    return res;
}

Stack* get_points(OrderedPointsList *list) {
    return list->best_stack;
}

PointDistance* get_ordered_points_first_point(OrderedPointsList* list) {
    if (stack_is_empty(list->best_stack))
        return NULL;
    else
        return stack_value(list->best_stack);
}