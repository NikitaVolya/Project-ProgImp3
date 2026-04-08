/**
 * @file point.h
 * @brief Point structure representing a classified point in multidimensional space.
 *
 * Provides operations for creating, copying, modifying,
 * and computing distances between points.
 */

#ifndef _POINT_H_
#define _POINT_H_

#include"vector.h"

/**
 * @struct Point
 * @brief Represents a point with a class label and position vector.
 *
 * @var Point::classe
 * Class label of the point.
 *
 * @var Point::position
 * Pointer to vector representing point coordinates.
 */
typedef struct {
    int classe;
    Vector *position;
} Point;

/**
 * @brief Creates a point with given class and position.
 * @warning The position vector is not copied; the pointer is stored directly.
 * @param[in] classe Class label of the point.
 * @param[in] position Pointer to position vector.
 * @return Pointer to created point.
 */
Point* create_point(int classe, Vector *position);

/**
 * @brief Creates a deep copy of a point.
 * @param[in] source Source point.
 * @return Pointer to copied point.
 */
Point* create_point_copy(Point *source);

/**
 * @brief Returns class label of the point.
 * @param[in] point Target point.
 * @return Class label.
 */
int get_point_classe(Point *point);

/**
 * @brief Returns value of point position at given dimension.
 * @param[in] point Target point.
 * @param[in] dimension Dimension index.
 * @return Coordinate value.
 */
float get_point_position(Point *point, size_t dimension);

/**
 * @brief Sets class label of the point.
 * @param[in, out] point Target point.
 * @param[in] classe New class label.
 */
void set_point_classe(Point *point, int classe);

/**
 * @brief Sets coordinate value at specified dimension.
 * @param[in, out] point Target point.
 * @param[in] dimension Dimension index.
 * @param[in] value New value.
 */
void set_point_position(Point *point, size_t dimension, float value);

/**
 * @brief Returns coordinate value at specified dimension.
 * @param[in] point Target point.
 * @param[in] dimension Dimension index.
 */
float get_point_position(Point *point, size_t dimension);

/**
 * @brief Returns number of dimensions of the point.
 * @param[in] point Target point.
 * @return Number of dimensions.
 */
size_t get_point_dimensions(Point *point);

/**
 * @brief Moves point to a new position.
 *
 * Copies all coordinate values from given vector.
 * Vectors must have the same number of dimensions.
 *
 * @param[in, out] point Target point.
 * @param[in] position New position vector.
 */
void move_point_to_position(Point *point, Vector *position);

/**
 * @brief Computes distance between two points.
 * @param[in] source First point.
 * @param[in] destination Second point.
 * @return Euclidean distance.
 */
float get_distance_to_point(Point *source, Point *destination);

/**
 * @brief Prints point to specified file stream.
 * @param[in] out Output file stream.
 * @param[in] point Point to print.
 */
void fprint_point(FILE *out, Point *point);

/**
 * @brief Prints point to standard output.
 * @param[in] point Point to print.
 */
void print_point(Point *point);

/**
 * @brief Frees memory allocated for a point.
 * @param[in] value Pointer to point.
 */
void free_point(void *point);

#endif /* _POINT_H_ */