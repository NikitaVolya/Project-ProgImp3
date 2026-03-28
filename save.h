/** 
* @file save.h
* @brief creation of fonction for data management
*
**/

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

/**
 * @struct Point
 * @brief Point: coordinates (dimension floats) and class label.
 */
typedef struct {
    float * pos;
    int classe;
} Point;

/**
 * @struct Data
 * @brief Dataset: points, counts, coordinate dimension.
 */
typedef struct {
    Point * points;
    int nb_points;
    int nb_classes;
    int dimension;
} Data;


/**
 * @def dim
 * @brief Represents the dimension of the points.
 */
#define dim 2


/**
 * @def path
 * @brief Represents the path of the file.
 */
#define path "create/data.txt"

/**
 * @brief Charges the data from a file.
 * @param[in] file The file to load data from.
 * @param[in,out] data The data structure to store the loaded data.
 */
void charge_file( Data * data);

/**
 * @brief Frees the data structure.
 * @param[in] data The data structure to free.
 */
void free_data(Data * data);

/**
 * @brief Displays the data structure.
 * @param[in] data The data structure to display.
 */
void display_data(Data data);

/**
 * @brief Saves the data structure to a file.
 * @param[in,out] data The data structure to save.
 */
int save_data(Data * data);

/**
 * @brief Adds a point to the data structure.
 * @param[in,out] data The data structure to add the point to.
 * @param[in] point The point to add.
 * @return 0 on success, 1 on failure.
 */
int add_point(Data * data, Point point);

/**
 * @brief Removes a point from the data structure.
 * @param[in,out] donnees The data structure to remove the point from.
 * @param[in] index The index of the point to remove.
 * @return 0 on success, 1 on failure.
 */
int remove_point(Data * data, int index) ;