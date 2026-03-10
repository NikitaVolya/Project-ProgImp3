/** 
* @file generate.h
* @brief creation of fonction for data generation
*
**/

#include<stdlib.h>
#include<stdio.h>
#include<time.h>



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
 * @brief Create or Recreate the file data.txt.
 */
FILE* create_file();

/**
 * @brief Generate point and save in the file
 * @param[in,out] file Pointer to the file data.txt.
  * @param[in] classe Number of classe. 
 */
void generate_point(FILE * file,int classe);

/**
 * @brief The procedure of generation of data
 * @param[in] n The Number of point.
 * @param[in] d The Number of dimension.
 * @param[in] c The Number of classe.
 */
int generate_data(int n, int d, int c);