#include <stdint.h>

struct matrix
{
	double** elements;
	uint32_t width;
	uint32_t height;
};

struct vector
{
	double* elements;
	uint32_t length;
};

void free_vector (struct vector* vector);

void free_matrix (struct matrix* matrix);

struct matrix transpose (struct matrix matrix);

struct vector matrix_vector_prod (struct matrix matrix, struct vector vector);

struct vector hadamard (struct vector vector1, struct vector vector2);

struct vector vector_add (struct vector vector1, struct vector vector2);

double dot_prod (struct vector vector1, struct vector vector2);

double vector_length (struct vector vector);

struct vector vector_map (struct vector to_map, double (*map_function)(double));
