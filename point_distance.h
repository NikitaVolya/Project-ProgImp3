#include<stdlib.h>
#include"point.h"

/**
 * @struct PointDistance
 * @brief Represents a point along with its distance to a reference point.
 *
 * @var PointDistance::point
 * Pointer to the point (usually a candidate neighbor).
 *
 * @var PointDistance::distance
 * Distance from the reference (target) point to this point.
 */
typedef struct {
    Point *point;
    double distance;
} PointDistance;

/**
 * @brief Checks whether a PointDistance pointer is NULL.
 *
 * If the given pointer is NULL, prints an error message to stderr
 * and terminates the program.
 *
 * @param[in] fname Name of the function calling this check.
 * @param[in] point_distance Pointer to PointDistance structure to validate.
 */
void check_point_distance_on_null(const char *fname, PointDistance *point_distance);

/**
 * @brief Creates a structure containing a point and its distance to another point.
 *
 * Computes the Euclidean distance between two points and stores
 * the result along with a pointer to the second point.
 *
 * @warning The points are not copied. Only pointers are stored.
 * Modifying the original points will affect the stored data.
 *
 * @param[in] point Reference point used to compute distance.
 * @param[in] target Point for which the distance is calculated.
 * @return Pointer to created PointDistance structure, or NULL on allocation failure.
 */
PointDistance* create_point_distance(Point *point, Point* target);

/**
 * @brief Returns the point stored in a PointDistance structure.
 *
 * @param[in] point_distance Target PointDistance structure.
 * @return Pointer to the stored point.
 */
Point* get_point_distance_point(PointDistance *point_distance);

/**
 * @brief Returns the distance value stored in a PointDistance structure.
 *
 * @param[in] point_distance Target PointDistance structure.
 * @return Distance value.
 */
double get_point_distance_value(PointDistance *point_distance);