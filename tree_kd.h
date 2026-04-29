#include "points_list.h"

/**
 * @struct tree_kd
 * @brief Node of a KD-tree storing a point and two children.
 *
 * Represents a binary space-partitioning tree used for nearest neighbor search.
 *
 * @var tree_kd::P
 * Pointer to the point stored in the node.
 *
 * @var tree_kd::left
 * Pointer to left subtree (values smaller on current dimension).
 *
 * @var tree_kd::right
 * Pointer to right subtree (values greater or equal on current dimension).
 */
typedef struct tree_kd {
    Point * P;
    struct tree_kd * right;
    struct tree_kd * left;
} tree_kd;

/**
 * @struct Zone
 * @brief Represents a bounding hyper-rectangle associated with a KD-tree node.
 *
 * Used during nearest neighbor search to prune branches.
 *
 * @var Zone::p_min
 * Minimum coordinates of the zone (lower bound).
 *
 * @var Zone::p_max
 * Maximum coordinates of the zone (upper bound).
 *
 * @var Zone::tree
 * Pointer to the corresponding KD-tree node.
 *
 * @var Zone::dimension
 * Current splitting dimension used in traversal.
 */
typedef struct {
    Vector *p_min, *p_max;
    tree_kd *tree;
    size_t dimension;
} Zone;

/**
 * @brief Checks if a KD-tree node is NULL.
 *
 * @param[in] t Tree node.
 * @return 1 if NULL, 0 otherwise.
 */
int is_empty_tree(tree_kd *t);

/**
 * @brief Returns an empty tree (NULL).
 *
 * @return NULL pointer representing an empty tree.
 */
tree_kd * empty_tree();

/**
 * @brief Creates a KD-tree node from a vector and class.
 *
 * Allocates a new node and copies the vector.
 *
 * @param[in] V Input vector.
 * @param[in] classe Class label of the point.
 * @return Pointer to created tree node.
 */
tree_kd * create_tree(Vector *V, int classe);

/**
 * @brief Builds a KD-tree from a points list.
 *
 * Inserts all points sequentially into a KD-tree.
 *
 * @param[in] list Input dataset.
 * @return Root of the created KD-tree.
 */
tree_kd* list_to_tree(PointsList* list);

/**
 * @brief Inserts a point into a KD-tree.
 *
 * Recursively selects left or right subtree based on splitting dimension.
 *
 * @param[in,out] t Tree root.
 * @param[in] v Point coordinates.
 * @param[in] classe Class label.
 */
void add_tree(tree_kd *t, Vector *v, int classe);

/**
 * @brief Prints a KD-tree in pre-order traversal.
 *
 * @param[in] t Tree root.
 * @param[in] tab Indentation level.
 */
void print_tree(tree_kd *t, size_t tab);
/**
 * @brief Frees a KD-tree recursively.
 *
 * @param[in] t Tree root.
 */
void free_tree(tree_kd *t);

/**
 * @brief Creates a zone associated with a KD-tree node.
 *
 * @param[in] tree Tree node.
 * @param[in] lt Lower bound vector.
 * @param[in] rd Upper bound vector.
 * @param[in] dimension Splitting dimension.
 * @return Allocated Zone structure.
 */
Zone* create_zone(tree_kd *tree, Vector *lt, Vector *rd, size_t dimension);

/**
 * @brief Creates the initial bounding zone for a KD-tree.
 *
 * Initializes the search space (default [-1, 1] per dimension).
 *
 * @param[in] tree Root node.
 * @return Initial zone.
 */
Zone* create_base_zone(tree_kd *tree);

/**
 * @brief Returns left child zone in KD-tree traversal.
 *
 * Updates bounding box according to split rule.
 *
 * @param[in] zone Current zone.
 * @return Left child zone or NULL.
 */
Zone* get_left_zone(Zone *zone);

/**
 * @brief Returns right child zone in KD-tree traversal.
 *
 * Updates bounding box according to split rule.
 *
 * @param[in] zone Current zone.
 * @return Right child zone or NULL.
 */
Zone* get_right_zone(Zone *zone);

/**
 * @brief Computes the closest point inside a zone to a given point.
 *
 * Projects the point onto the bounding hyper-rectangle.
 *
 * @param[in] zone Search zone.
 * @param[in] p Input point.
 * @return Projected point inside zone.
 */
Point* nearby_zone_point(Zone *zone, Point *p); 

/**
 * @brief Checks if a point is inside a zone.
 *
 * @param[in] zone Search zone.
 * @param[in] p Point to test.
 * @return 1 if inside, 0 otherwise.
 */
int check_point_in_zone(Zone *zone, Point *p);

/**
 * @brief Frees a zone structure.
 *
 * Does not free the associated KD-tree node.
 *
 * @param[in] zone Zone to free.
 */
void free_zone(Zone *zone);

/**
 * @brief Finds k nearest neighbors in KD-tree.
 *
 * Initializes search zone and returns k closest points.
 *
 * @param[in] tree KD-tree root.
 * @param[in] target Query point.
 * @param[in] k Number of neighbors.
 * @return Stack of k nearest points.
 */
Stack* tree_select_k_nearby(tree_kd *tree, Point *target, int k);

/**
 * @brief Classifies a point using KD-tree KNN algorithm.
 *
 * Builds a KD-tree, performs nearest neighbor search,
 * and assigns majority class to target.
 *
 * @param[in] list Dataset.
 * @param[in,out] target Point to classify.
 * @param[in] k Number of neighbors.
 * @return Predicted class.
 */
int select_tree_class(PointsList *list, Point *target, int k);
