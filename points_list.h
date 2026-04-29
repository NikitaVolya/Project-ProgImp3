#ifndef _POINTS_LIST_H_
#define _POINTS_LIST_H_

#include<stdlib.h>
#include<stdio.h>
#include"ordered_points_list.h"


/**
 * @struct PointsList
 * @brief Dynamic container for storing a collection of points.
 *
 * This structure represents a resizable array of Point pointers,
 * used for datasets in algorithms such as K-Nearest Neighbors (KNN).
 *
 * @var PointsList::points
 * Array of pointers to stored points.
 *
 * @var PointsList::capacity
 * Current allocated capacity of the array.
 *
 * @var PointsList::count
 * Number of points currently stored in the list.
 *
 * @var PointsList::nb_classes
 * Total number of possible classes in the dataset.
 *
 * @var PointsList::dimensions
 * Number of dimensions for each point in the dataset.
 */
typedef struct {
    Point **points;
    size_t capacity, count;
    int nb_classes, dimensions;
} PointsList;


/**
 * @brief Creates a dynamic list of points.
 *
 * Allocates memory for a list and its internal array of point pointers.
 *
 * @param[in] start_capacity Initial capacity of the list.
 * @param[in] nb_classes Number of possible classes.
 * @param[in] dimensions Number of dimensions for each point.
 * @return Pointer to created PointsList or NULL on failure.
 */
PointsList* create_points_list(size_t start_capacity, int nb_classes, int dimensions);

/**
 * @brief Adds a point to the list.
 *
 * Automatically resizes internal array if capacity is exceeded.
 *
 * @param[in, out] list Target list.
 * @param[in] point Point to add.
 */
void points_list_add_point(PointsList *list, Point *point);

/**
 * @brief Removes a point from the list at given index.
 *
 * Replaces removed element with the last element (unordered removal).
 * Frees memory of removed point.
 *
 * @param[in, out] list Target list.
 * @param[in] index Index of point to remove.
 */
void points_list_remove_point(PointsList *list, size_t index);

/**
 * @brief Returns a point at given index.
 *
 * @param[in] list Target list.
 * @param[in] index Index of point.
 * @return Pointer to point.
 */
Point* points_list_get_point(PointsList *list, size_t index);

/**
 * @brief Replaces a point at a given index.
 *
 * @param[in, out] list Target list.
 * @param[in] index Index to modify.
 * @param[in] p New point.
 */
void points_list_set_point(PointsList *list, size_t index, Point *p);

/**
 * @brief Returns number of points in the list.
 *
 * @param[in] list Target list.
 * @return Number of stored points.
 */
size_t points_list_get_count(PointsList *list);

/**
 * @brief Prints a formatted representation of the list to a file.
 *
 * @param[in] file Output stream.
 * @param[in] list Target list.
 */
void fprint_points_list(FILE *file, PointsList *list);

/**
 * @brief Prints the list to standard output.
 *
 * @param[in] list Target list.
 */
void print_points_list(PointsList *list);

/**
 * @brief Frees all memory associated with the list.
 *
 * Also frees all stored points.
 *
 * @param[in] list Target list.
 */
void free_points_list(PointsList *list);

/**
 * @brief Extracts the majority class from a stack of nearest neighbors.
 *
 * Counts occurrences of each class and returns the most frequent one.
 * Frees all stack elements during processing.
 *
 * Free stack in process.
 *
 * @param[in] stack Stack of PointDistance elements.
 * @param[in] nb_classes Number of possible classes.
 * @return Majority class or -1 on error.
 */
int extract_majority_class_from_stack(Stack *stack, int nb_classes);

/**
 * @brief Selects k nearest neighbors from the dataset.
 *
 * Uses a bounded ordered structure to keep only k closest points.
 *
 * @param[in] list Source dataset.
 * @param[in] target Reference point.
 * @param[in] k Number of nearest neighbors to keep.
 * @return Stack containing k nearest PointDistance elements.
 */
Stack* point_list_select_k_nearby(PointsList *list, Point *target, int k);

/**
 * @brief Classifies a point using brute-force KNN.
 *
 * Finds k nearest neighbors and assigns the most frequent class
 * to the target point.
 *
 * @param[in] list Dataset.
 * @param[in, out] target Point to classify.
 * @param[in] k Number of neighbors.
 * @return Predicted class or -1 on error.
 */
int select_class_bf(PointsList *list, Point *point, int k);

#endif /* _POINTS_LIST_H_ */