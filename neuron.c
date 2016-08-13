#include <stdlib.h>

#include "neuron.h"
#include "linear.h"

struct neuron_layer* create_input_layer (uint32_t size)
{
	int i;

	struct vector bias_vector;
	struct neuron_layer* ret = (struct neuron_layer*)malloc(sizeof(struct neuron_layer));

	bias_vector.length = size;
	bias_vector.elements = (double*)malloc(size * sizeof(double));
	for (i = 0; i < size; i++)
		bias_vector.elements[i] = 0;

	ret->bias_vector = bias_vector;

	ret->prev_layer = NULL;
	ret->next_layer = NULL;

	return ret;
}

struct neuron_layer* add_neuron_layer(struct neuron_layer* prev_layer, struct matrix weight_matrix, struct vector bias_vector)
{
	struct neuron_layer* to_add = (struct neuron_layer*)malloc(sizeof(struct neuron_layer));

	to_add->weight_matrix = weight_matrix;
	to_add->weight_matrix_buf = copy_matrix(weight_matrix);
	to_add->bias_vector = bias_vector;
	to_add->bias_vector_buf = copy_vector(bias_vector);

	to_add->prev_layer = prev_layer;
	prev_layer->next_layer = to_add;

	to_add->next_layer = NULL;

	return to_add;
}

void free_network(struct neuron_layer* to_free)
{
	free_matrix(&(to_free->weight_matrix));
	free_matrix(&(to_free->weight_matrix_buf));
	free_vector(&(to_free->bias_vector));
	free_vector(&(to_free->bias_vector_buf));
	free_vector(&(to_free->z_value_vector));
	free_vector(&(to_free->activation_value_vector));
	free_vector(&(to_free->error_vector));

	if (to_free->next_layer != NULL)
		free_network(to_free->next_layer);
	
	free(to_free);
}

struct vector simulate_network(struct neuron_layer* input_layer)
{
	struct vector z_value_vector;
	struct vector tmp;

	if (input_layer->prev_layer != NULL)
	{
		tmp = matrix_vector_prod(input_layer->weight_matrix, input_layer->prev_layer->activation_value_vector);
		z_value_vector = vector_add(tmp, input_layer->bias_vector);
		input_layer->z_value_vector = z_value_vector;
		free_vector(&tmp);

		input_layer->activation_value_vector = vector_map(z_value_vector, activation_function);
	}

	if (input_layer->next_layer != NULL)
		return simulate_network(input_layer->next_layer);
	else
		return input_layer->activation_value_vector;
}
