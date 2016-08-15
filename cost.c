#include "cost.h"
#include "linear.h"

double quadratic_cost_function (struct vector expected_output, struct vector actual_output)
{
	struct vector negative_actual = scalar_vector_prod(actual_output, -1);
	struct vector tmp = vector_add(expected_output, negative_actual);
	double length = vector_length(tmp);

	free_vector(&tmp);
	free_vector(&negative_actual);

	return length * length / 2;
}

struct vector nabla_quadratic_cost (struct vector expected_output, struct vector actual_output)
{
	struct vector negative_expected = scalar_vector_prod(expected_output, -1);
	struct vector ret = vector_add(negative_expected, actual_output);

	free_vector(&negative_expected);

	return ret;
}
