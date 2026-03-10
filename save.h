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
 * @brief Represents a point in 2-dimensional space.
 *
 * @var Point::x
 * x coordinate of the point.
 *
 * @var Point::y
 * y coordinate of the point.
 *
 * @var Point::classe
 * classe of the point.
 */

typedef struct {
    float x;
    float y;
    int classe;
} Point;

/**
 * @struct Data
 * @brief Represents a data structure for storing points.
 *
 * @var Data::points
 * Pointer to dynamically allocated array of Point.
 *
 * @var Data::nb_points
 * Number of points.
 *
 * @var Data::nb_classes
 * Number of classes.
 */
typedef struct {
    Point * points;
    int nb_points;
    int nb_classes;
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
void charge_file(FILE * file, Data * data);

/**
 * @brief Frees the data structure.
 * @param[in] data The data structure to free.
 */
void free_donnees(Data * data);

/**
 * @brief Displays the data structure.
 * @param[in] data The data structure to display.
 */
void display_donnees(Data * data);

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