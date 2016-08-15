#include <math.h>

#include "sigmoid.h"

double sigmoid_activation_function (double z)
{
	return 1.0 / (1.0 + exp(-z));
}

double derivative_sigmoid_activation_function (double z)
{
	sigmoid_activation_function(z) * (1 - sigmoid_activation_function(z));
}
