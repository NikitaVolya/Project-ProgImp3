#include"stack.h"
#include"point_distance.h"

/**
 * @struct OrderedPointsList
 * @brief Maintains a sorted list of nearest points using two stacks.
 *
 * Stores up to maxsize elements of type PointDistance,
 * ordered by increasing distance (closest points first).
 *
 * Internally uses two stacks:
 * - best_stack: stores the current best candidates
 * - tmp_stack: temporary stack used during insertion
 *
 * @var OrderedPointsList::best_stack
 * Stack containing the current nearest points of type PointDistance.
 *
 * @var OrderedPointsList::tmp_stack
 * Temporary stack used for reordering during insertion.
 *
 * @var OrderedPointsList::maxsize
 * Maximum number of points stored in the list.
 */
typedef struct {
    Stack *best_stack, *tmp_stack;
    size_t maxsize;
} OrderedPointsList;

/**
 * @brief Creates an ordered list for nearest neighbor search.
 *
 * Initializes internal stacks and sets maximum capacity.
 *
 * @param[in] maxsize Maximum number of points to store.
 * @return Pointer to created list, or NULL on allocation failure.
 */
OrderedPointsList* create_ordered_point_list(size_t maxsize);

/**
 * @brief Frees memory allocated for the ordered points list.
 *
 * Frees both internal stacks and the list itself.
 *
 * @param[in] list Target list to free.
 */
void free_ordered_points_list(OrderedPointsList* list);

/**
 * @brief Adds a point to the ordered list based on its distance to target.
 *
 * Computes the distance between the given point and target,
 * then inserts it into the list while preserving order.
 *
 * If the list exceeds maxsize, the farthest points are discarded.
 *
 * @param[in, out] list Target ordered list.
 * @param[in] point Candidate point.
 * @param[in] target Reference point.
 * @return Pointer to updated list.
 */
OrderedPointsList* ordered_points_list_add_point(OrderedPointsList* list, Point *point, Point *target);

/**
 * @brief Extracts all stored points as a stack.
 *
 * Transfers ownership of the internal stack to the caller
 * and replaces it with a new empty stack.
 *
 * @param[in, out] list Target list.
 * @return Stack containing stored PointDistance elements.
 */
Stack* extract_points(OrderedPointsList *list);

/**
 * @brief Returns the internal stack of stored points.
 *
 * @warning The returned pointer is not a copy.
 *
 * @param[in] list Target list.
 * @return Pointer to internal stack stored PointDistance elements.
 */
Stack* get_points(OrderedPointsList *list);

/**
 * @brief Returns the first element from the ordered list.
 *
 * @warning The returned pointer is not a copy.
 *
 * @param[in] list Target list.
 * @return Pointer to PointDistance or NULL if list is empty.
 */
PointDistance* get_ordered_points_first_point(OrderedPointsList* list);