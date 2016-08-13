#include <stdlib.h>

#include "error.h"
#include "linear.h"

void free_vector (struct vector* vector)
{
	free(vector->elements);
}

void free_matrix (struct matrix* matrix)
{
	int i;

	for (i = 0; i < matrix->height; i++)
	{
		free (matrix->elements[i]);
	}

	free (matrix->elements);
}

struct matrix transpose (struct matrix matrix)
{
	struct matrix ret;
	int i;
	int j;

	ret.height = matrix.width;
	ret.width = matrix.height;
	ret.elements = (double**)malloc(ret.height * sizeof(double*));

	for (i = 0; i < ret.height; i++)
		ret.elements[i] = (double*)malloc(ret.width * sizeof(double));

	for (i = 0; i < matrix.height; i++)
	{
		for (j = 0; j < matrix.width; j++)
			ret.elements[j][i] = matrix.elements[i][j];
	}

	return ret;
}

struct vector matrix_vector_prod (struct matrix matrix, struct vector vector)
{
	struct vector ret;
	double temp_sum;
	int i;
	int j;

	if (matrix.width != vector.length)
		error(err_invalid_op, __LINE__, __FILE__, "Matrix width does not match vector length");

	ret.length = matrix.height;
	ret.elements = (double*)malloc(ret.length * sizeof(double));

	for (i = 0; i < matrix.height; i++)
	{
		temp_sum = 0;
		for (j = 0; j < vector.length; j++)
			temp_sum += vector.elements[j] * matrix.elements[i][j];

		ret.elements[i] = temp_sum;
	}

	return ret;
}

struct vector hadamard (struct vector vector1, struct vector vector2)
{
	struct vector ret;
	int i;

	if (vector1.length != vector2.length)
		error(err_invalid_op, __LINE__, __FILE__, "Hadamard product only possible with vectors of same length");

	ret.length = vector1.length;
	ret.elements = (double*)malloc(ret.length * sizeof(double));

	for (i = 0; i < vector1.length; i++)
		ret.elements[i] = vector1.elements[i] * vector2.elements[i];

	return ret;
}

double dot_prod (struct vector vector1, struct vector vector2)
{
	double ret = 0;
	int i;

	if (vector1.length != vector2.length)
		error(err_invalid_op, __LINE__, __FILE__, "Dot product requires two vectors of same length");

	for (i = 0; i < vector1.length; i++)
		ret += vector1.elements[i] * vector2.elements[i];

	return ret;
}

double vector_length (struct vector vector)
{
	return dot_prod (vector, vector);
}

struct vector vector_map (struct vector to_map, double (*map_function)(double))
{
	struct vector ret;
	int i;

	ret.elements = (double*)malloc(to_map.length * sizeof(double));

	for (i = 0; i < to_map.length; i++)
		ret.elements[i] = map_function(to_map.elements[i]);

	return ret;
}

struct vector vector_add (struct vector vector1, struct vector vector2)
{
	struct vector ret;
	int i;

	if (vector1.length != vector2.length)
		error(err_invalid_op, __LINE__, __FILE__, "Vector addition requires vectors to be same length");

	ret.length = vector1.length;
	ret.elements = (double*)malloc(ret.length * sizeof(double));

	for (i = 0; i < vector1.length; i++)
		ret.elements[i] = vector1.elements[i] + vector2.elements[i];

	return ret;
}

struct matrix vector_to_matrix (struct vector vector)
{
	struct matrix ret;
	int i;

	ret.width = 1;
	ret.height = vector.length;

	ret.elements = (double**)malloc(vector.length * sizeof(double*));
	for (i = 0; i < ret.height; i++)
	{
		ret.elements[i] = (double*)malloc(sizeof(double));
		ret.elements[i][0] = vector.elements[i];
	}

	return ret;
}

struct matrix matrix_matrix_prod (struct matrix matrix1, struct matrix matrix2)
{
	struct matrix ret;
	int i;
	int j;
	int k;
	double sum;

	if (matrix1.width != matrix2.height)
		error(err_invalid_op, __LINE__, __FILE__, "Matrix multiplications requires the first matrix have the width of the second");

	ret.width = matrix2.width;
	ret.height = matrix1.height;

	ret.elements = (double**)malloc(ret.height * sizeof(double*));
	for (i = 0; i < ret.height; i++)
		ret.elements[i] = (double*)malloc(ret.width * sizeof(double));
	
	for (i = 0; i < matrix2.width; i++)
	{
		for (j = 0; j < matrix1.height; j++)
		{
			sum = 0;
			for (k = 0; k < matrix2.height; k++)
				sum += matrix1.elements[j][k] * matrix2.elements[k][i];

			ret.elements[j][i] = sum;
		}
	}

	return ret;
}

struct matrix matrix_add (struct matrix matrix1, struct matrix matrix2)
{
	struct matrix ret;
	int i;
	int j;

	if (matrix1.width != matrix2.width || matrix1.height != matrix2.height)
		error(err_invalid_op, __LINE__, __FILE__, "Matrix addition requires the matrices to have identical dimensions");

	ret.width = matrix1.width;
	ret.height = matrix2.height;

	ret.elements = (double**)malloc(ret.height * sizeof(double*));

	for (i = 0; i < matrix1.height; i++)
	{
		ret.elements[i] = (double*)malloc(ret.width * sizeof(double));

		for (j = 0; j < matrix1.width; j++)
			ret.elements[i][j] = matrix1.elements[i][j] + matrix2.elements[i][j];
	}

	return ret;
}

struct matrix scalar_matrix_prod (struct matrix matrix, double scalar)
{
	struct matrix ret;
	int i;
	int j;

	ret.width = matrix.width;
	ret.height = matrix.height;

	ret.elements = (double**)malloc(ret.height * sizeof(double*));

	for (i = 0; i < matrix.height; i++)
	{
		ret.elements[i] = (double*)malloc(ret.width * sizeof(double));

		for (j = 0; j < matrix.width; j++)
			ret.elements[i][j] = matrix.elements[i][j] * scalar;
	}

	return ret;
}

struct vector scalar_vector_prod (struct vector vector, double scalar)
{
	struct vector ret;
	int i;

	ret.length = vector.length;
	ret.elements = (double*)malloc(ret.length * sizeof(double));

	for (i = 0; i < vector.length; i++)
		ret.elements[i] = vector.elements[i] * scalar;

	return ret;
}

struct matrix copy_matrix (struct matrix matrix)
{
	struct matrix ret;
	int i;
	int j;

	ret.width = matrix.width;
	ret.height = matrix.height;

	ret.elements = (double**)malloc(ret.height * sizeof(double*));

	for (i = 0; i < matrix.width; i++)
	{
		ret.elements[i] = (double*)malloc(ret.width * sizeof(double));

		for (j = 0; i < matrix.width; j++)
			ret.elements[i][j] = matrix.elements[i][j];
	}

	return ret;
}

struct vector copy_vector (struct vector vector)
{
	struct vector ret;
	int i;

	ret.length = vector.length;

	ret.elements = (double*)malloc(ret.length * sizeof(double));

	for (i = 0; i < vector.length; i++)
		ret.elements[i] = vector.elements[i];
}
