/** 
* @file save.h
* @brief creation of fonction for data management
*
**/
#include<stdio.h>
#include"points_list.h"

/** @brief
* @param[in] list list of point
* @return int return a value of exit code
*/
Point* scan_point(FILE *file, size_t dimensions);

/** @brief load data from a file into a pointlist
* @param[in] file file input data
* @return pointlist return the list of point
*/
PointsList* load_points_from_file(FILE *file);
/** @brief save the data of pointlist into a file
 * @param[in] list list of point
 * @param[in] file file of save
 * @return int return a value of exit code
 */
int save_data_to_file(PointsList *list, FILE *file);