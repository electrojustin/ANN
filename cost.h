#include "linear.h"

#ifndef COST_H
#define COST_H
double quadratic_cost_function (struct vector expected_output, struct vector actual_output);

struct vector nabla_quadratic_cost (struct vector expected_output, struct vector actual_output);
#endif
