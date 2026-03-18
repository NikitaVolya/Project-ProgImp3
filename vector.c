#include"vector.h"

/**
 * @brief Validates that the given vector pointer is not NULL.
 *
 * If the pointer is NULL, prints an error message to stderr
 * including the function name and terminates the program.
 *
 * @param[in] function_name Name of the calling function.
 * @param[in] v Pointer to vector to validate.
 */
inline void check_on_null(const char *function_name, Vector *v) {
    if (v == NULL) {
        fprintf(stderr, "%s interrupted\nVector is NULL\n", function_name);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Validates that two vectors have equal dimensions.
 *
 * If the dimensions differ, prints an error message to stderr
 * including the function name and terminates the program.
 *
 * @param function_name Name of the calling function.
 * @param a First vector.
 * @param b Second vector.
 */
inline void check_on_dimensions(const char *function_name, Vector *a, Vector *b) {
    if (a->dimensions != b->dimensions) {
        fprintf(stderr, "%s interrupted\nVectors\n", function_name);
        exit(EXIT_FAILURE);
    }
}

Vector* create_vector_zero(size_t dimensions) {
    Vector *res;

    /* check on valide dimension */
    if (dimensions == 0) {
        fprintf(stderr, "Error, unable to create a vector with 0 dimensions\n");
        return NULL;
    }

    /* allocation of Vector */
    if ((res = (Vector*) malloc(sizeof(Vector))) == NULL) {
        fprintf(stderr, "create_vector_zero interrupted\nError while memory allocation\n");
        exit(EXIT_FAILURE);
    }

    /* allocation values array */
    if ((res->values = (float*) calloc(dimensions, sizeof(float))) == NULL) {
        fprintf(stderr, "create_vector_wero interrupted\nError while memory allocation\n");
        exit(EXIT_FAILURE);
    }

    res->dimensions = dimensions;
    return res;
}

Vector* create_vector(size_t dimensions) {
    Vector *res;
    
    /* check on valide dimension */
    if (dimensions == 0) {
        fprintf(stderr, "Error, unable to create a vector with 0 dimensions\n");
        return NULL;
    }

    /* allocation of Vector */
    if ((res = (Vector*) malloc(sizeof(Vector))) == NULL) {
        fprintf(stderr, "create_vector interrupted\nError while memory allocation\n");
        exit(EXIT_FAILURE);
    }

    /* allocation values array */
    if ((res->values = (float*) malloc(sizeof(float) * dimensions)) == NULL) {
        fprintf(stderr, "create_vector interrupted\nError while memory allocation\n");
        exit(EXIT_FAILURE);
    }

    res->dimensions = dimensions;
    return res;
}

Vector* create_vector_copy(Vector *source) {
    Vector *res;
    size_t i;

    /* allocation of Vector */
    if ((res = (Vector*) malloc(sizeof(Vector))) == NULL) {
        fprintf(stderr, "create_vector_copy interrupted\nError while memory allocation\n");
        exit(EXIT_FAILURE);
    }

    res->dimensions = source->dimensions;
    
    /* allocation values array */
    if ((res->values = (float*) malloc(sizeof(float) * res->dimensions)) == NULL) {
        fprintf(stderr, "create_vector_copy interrupted\nError while memory allocation\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < res->dimensions; i++) {
        res->values[i] = source->values[i];
    }

    return res;
}

Vector* create_vector_with_values(size_t dimensions, ...) {
    Vector *res;
    va_list args;
    float value;
    size_t i;

    /* creating of vector */
    if ((res = create_vector(dimensions)) == NULL) {
        return NULL;
    }

    /* inserting values from va_list */
    va_start(args, dimensions);

    for (i = 0; i < dimensions; i++) {
        value = (float) va_arg(args, double);
        res->values[i] = value;
    }

    va_end(args);

    return res;
}

inline Vector* create_vector2_zero() {
    return create_vector_zero(2);
}

inline Vector* create_vector2() {
    return create_vector(2);
}

inline Vector* create_vector2_with_values(float x, float y) {
    return create_vector_with_values(2, (double) x, (double) y);
}

void free_vector(Vector *vector) {
    /* free if vector is not NULL */
    if (vector != NULL) {
        free(vector->values);
        free(vector);
    }
}


float* get_vector_element(Vector *vector, size_t index) {
    float *res;

    /* check input data */
    check_on_null("Vector function", vector);

    /* check on index out of range of vector dimension */
    if (index >= vector->dimensions) {
        fprintf(stderr, "Vector function interrupted\nIndex out of bounds\n");
        exit(EXIT_FAILURE);
    }

    res = &vector->values[index];

    return res;
}

float get_vector_value(Vector *vector, size_t index) {
    float *res;

    res = get_vector_element(vector, index);

    return *res;
}

size_t get_vector_dimensions(Vector *vector) {
    
    /* check input data */
    check_on_null("get_vector_dimensions", vector);

    return vector->dimensions;
}

float get_vector_length(Vector *vector) {
    float sum, res;
    size_t i;

    sum = 0.0f;

    /* check input data */
    check_on_null("get_vector_length", vector);

    for (i = 0; i < vector->dimensions; i++) {
        sum += vector->values[i] * vector->values[i];
    }

    res = sqrtf(sum);

    return res;
}

float get_distance(Vector *a, Vector *b) {
    Vector *tmp;
    float res;

    tmp = sub_vector(b, a);
    res = get_vector_length(tmp);

    free_vector(tmp);
    return res;
}

void set_vector_value(Vector *vector, size_t index, float value) {
    float *v_value;
    
    /* check input data */
    check_on_null("set_vector_value", vector);

    v_value = get_vector_element(vector, index);

    *v_value = value;
}


Vector* add_to_vector(Vector *dest, Vector *v) {
    size_t i;
    
    /* check input data */
    check_on_null("add_to_vector", dest);
    check_on_null("add_to_vector", v);
    check_on_dimensions("add_to_vector", dest, v);

    /* adding values */
    for (i = 0; i < v->dimensions; i++) {
        dest->values[i] += v->values[i];
    }

    return dest;
}

Vector* sub_to_vector(Vector *dest, Vector *v) {
    size_t i;

    /* check input data */
    check_on_null("sub_to_vector", dest);
    check_on_null("sub_to_vector", v);
    check_on_dimensions("sub_to_vector", dest, v);

    /* subtructing values */
    for (i = 0; i < v->dimensions; i++) {
        dest->values[i] -= v->values[i];
    }

    return dest;
}

Vector* mult_to_vector(Vector *dest, float value) {
    size_t i;

    /* check input data */
    check_on_null("mult_to_vector", dest);

    /* mult value */
    for (i = 0; i < dest->dimensions; i++) {
        dest->values[i] *= value;
    }

    return dest;
}


Vector* add_vector(Vector *first, Vector *second) {
    Vector *res;

    /* check input data */
    check_on_null("add_vector", first);
    check_on_null("add_vector", second);
    check_on_dimensions("add_vector", first, second);

    res = create_vector_copy(first);

    add_to_vector(res, second);

    return res;
}

Vector* sub_vector(Vector *first, Vector *second) {
    Vector *res;
    
    /* check input data */
    check_on_null("sub_vector", first);
    check_on_null("sub_vector", second);
    check_on_dimensions("sub_vector", first, second);

    res = create_vector_copy(first);

    sub_to_vector(res, second);

    return res;
}

Vector* mult_vector(Vector *vector, float value) {
    Vector *res;

    /* check input data */
    check_on_null("mult_vector", vector);

    res = create_vector_copy(vector);

    mult_to_vector(res, value);

    return res;
}

void fprint_vector(FILE *file, Vector *vector) {
    size_t i;

    if (vector == NULL) {
        /* printing if vector is NULL */
        fprintf(file, "Vector is NULL\n");
    } else {
        fprintf(file, "< Vector : %zu [ ", vector->dimensions);

        /* printing vector values */
        for (i = 0; i < vector->dimensions; i++) {
            if (i != 0)
                fprintf(file, ", ");
            fprintf(file, "%f", vector->values[i]);
        }

        fprintf(file, " ] >\n");
    }
}

inline void print_vector(Vector *vector) {
    fprint_vector(stdout, vector);
}