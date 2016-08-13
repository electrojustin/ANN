#include <stdlib.h>

#include "backprop.h"
#include "linear.h"
#include "train.h"
#include "neuron.h"

void compute_output_error (struct neuron_layer* output_layer, struct vector training_output)
{
	struct vector tmp = vector_map(output_layer->z_value_vector, derivative_activation_function);
	struct vector tmp2 = nabla_cost_function(training_output, output_layer->activation_value_vector);

	output_layer->error_vector = hadamard(tmp, tmp2);

	free_vector(&tmp);
	free_vector(&tmp2);
}

void compute_error (struct neuron_layer* layer)
{
	struct vector tmp = vector_map(layer->z_value_vector, derivative_activation_function);
	struct matrix weight_transpose = transpose(layer->next_layer->weight_matrix);
	struct vector tmp2 = matrix_vector_prod(weight_transpose, layer->next_layer->error_vector);

	layer->error_vector = hadamard(tmp, tmp2);

	free_vector(&tmp);
	free_vector(&tmp2);

	if (layer->prev_layer != NULL)
		compute_error(layer->prev_layer);
}

void backpropagate (struct neuron_layer* output_layer, struct vector training_output)
{
	compute_output_error(output_layer, training_output);
	compue_error(output_layer->prev_layer);
}
