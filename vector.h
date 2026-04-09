/**
 * @file vector.h
 * @brief Vector structure for storing a point in multidimensional space.
 *
 * Provides basic operations for dynamic vectors, including creation,
 * arithmetic operations, accessors, and memory management.
 */

#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<math.h>


/**
 * @struct Vector
 * @brief Represents a vector in N-dimensional space.
 *
 * @var Vector::values
 * Pointer to dynamically allocated array of float values.
 *
 * @var Vector::dimensions
 * Number of dimensions (size of the vector).
 */
typedef struct {
    float *values;
    size_t dimensions;
} Vector;

/**
 * @brief Creates a zero-initialized vector of given dimension.
 * @param[in] dimensions Number of dimensions.
 * @return Pointer to created vector.
 */
Vector* create_vector_zero(size_t dimensions);

/**
 * @brief Creates an uninitialized vector of given dimension.
 * @param[in] dimensions Number of dimensions.
 * @return Pointer to created vector.
 */
Vector* create_vector(size_t dimensions);

/**
 * @brief Creates a vector with specified values.
 * @param[in] dimensions Number of dimensions.
 * @param[in] ... Double values for each dimension.
 * @return Pointer to created vector.
 */
Vector* create_vector_with_values(size_t dimensions, ...);

/**
 * @brief Creates a 2D zero-initialized vector.
 * @return Pointer to created vector.
 */
Vector* create_vector2_zero();

/**
 * @brief Creates an uninitialized 2D vector.
 * @return Pointer to created vector.
 */
Vector* create_vector2();

/**
 * @brief Creates a copy of the given vector.
 * @param[in] source Source vector.
 * @return Pointer to copied vector.
 */
Vector* create_vector_copy(Vector *source);

/**
 * @brief Creates a 2D vector with specified values.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @return Pointer to created vector.
 */
Vector* create_vector2_with_values(float x, float y);

/**
 * @brief Frees memory allocated for a vector.
 * @param[in] value Vector to free.
 */
void free_vector(Vector *value);

/**
 * @brief Returns value at specified index.
 * @param[in] vector Target vector.
 * @param[in] index Index of dimension.
 * @return Value at index.
 */
float get_vector_value(Vector *vector, size_t index);

/**
 * @brief Returns number of dimensions.
 * @param[in] vector Target vector.
 * @return Number of dimensions.
 */
size_t get_vector_dimensions(Vector *vector);

/**
 * @brief Computes Euclidean length of vector.
 * @param[in] vector Target vector.
 * @return Vector length.
 */
double get_vector_length(Vector *vector);

/**
 * @brief Computes Euclidean distance beetwen two vectors
 * @param[in] a First vector.
  * @param[in] b Second vector.
 * @return distance.
 */
double get_distance(Vector *a, Vector *b);

/**
 * @brief Sets value at specified index.
 * @param[in, out] vector Target vector.
 * @param[in] index Index of dimension.
 * @param[in] value New value.
 */
void set_vector_value(Vector *vector, size_t index, float value);

/**
 * @brief Adds vector v to dest (in-place).
 * @param[in, out] dest Destination vector.
 * @param[in] v Vector to add.
 * @return Pointer to dest.
 */
Vector* add_to_vector(Vector *dest, Vector *v);

/**
 * @brief Subtracts vector v from dest (in-place).
 * @param[in, out] dest Destination vector.
 * @param[in] v Vector to subtract.
 * @return Pointer to dest.
 */
Vector* sub_to_vector(Vector *dest, Vector *v);

/**
 * @brief Multiplies vector by scalar (in-place).
 * @param[in, out] dest Target vector.
 * @param[in] value Scalar multiplier.
 * @return Pointer to dest.
 */
Vector* mult_to_vector(Vector *dest, float value);


/**
 * @brief Returns new allocated vector as sum of two vectors.
 * @param[in] first First vector.
 * @param[in] second Second vector.
 * @return New resulting vector.
 */
Vector* add_vector(Vector *first, Vector *second);

/**
 * @brief Returns new allocated vector as difference of two vectors.
 * @param[in] first First vector.
 * @param[in] second Second vector.
 * @return New resulting vector.
 */
Vector* sub_vector(Vector *first, Vector *second);

/**
 * @brief Returns new vector multiplied by scalar.
 * @param[in] vector Source vector.
 * @param[in] value Scalar multiplier.
 * @return New resulting vector.
 */
Vector* mult_vector(Vector *vector, float value);

/**
 * @brief Prints vector to specified file.
 * @param[in] file Output file stream.
 * @param[in] vector Vector to print.
 */
void fprint_vector(FILE *file, Vector *vector);

/**
 * @brief Prints vector to standard output.
 * @param[in] vector Vector to print.
 */
void print_vector(Vector *vector);