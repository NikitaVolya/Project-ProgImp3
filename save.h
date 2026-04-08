/** 
* @file save.h
* @brief creation of fonction for data management
*
**/
#include<stdio.h>
#include"points_list.h"


Point* scan_point(FILE *file, size_t dimensions);

PointsList* load_points_from_file(FILE *file);

int save_data_to_file(PointsList *list, FILE *file);