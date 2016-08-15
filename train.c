#include <stdlib.h>

#include "linear.h"
#include "backprop.h"
#include "train.h"
#include "neuron.h"

void flush_weights_and_biases (struct neuron_layer* layer)
{
	free_matrix(&(layer->weight_matrix));
	free_vector(&(layer->bias_vector));

	layer->weight_matrix = layer->weight_matrix_buf;
	layer->bias_vector = layer->bias_vector_buf;

	layer->weight_matrix_buf = copy_matrix(layer->weight_matrix);
	layer->bias_vector_buf = copy_vector(layer->bias_vector);
}

void update_weight_buffers (struct neuron_layer* layer, double training_rate, uint32_t batch_size)
{
	struct matrix tmp;
	struct matrix tmp2;
	struct matrix tmp3;

	tmp = vector_to_matrix(layer->error_vector);
	tmp2 = vector_to_matrix(layer->prev_layer->activation_value_vector);
	tmp3 = transpose (tmp2);
	free_matrix(&tmp2);
	free_vector(&(layer->prev_layer->activation_value_vector));
	free_vector(&(layer->prev_layer->z_value_vector));
	
	tmp2 = matrix_matrix_prod(tmp, tmp3);
	free_matrix(&tmp);
	free_matrix(&tmp3);

	tmp = scalar_matrix_prod(tmp2, -1 * training_rate / batch_size);
	free_matrix(&tmp2);

	tmp2 = matrix_add(layer->weight_matrix_buf, tmp);
	free_matrix(&(layer->weight_matrix_buf));
	layer->weight_matrix_buf = tmp2;
	free_matrix(&tmp);

	if (layer->next_layer != NULL)
		update_weight_buffers(layer->next_layer, training_rate, batch_size);
}

//Note: must only be called *after* update_weight_buffers
void update_bias_buffers (struct neuron_layer* layer, double training_rate, uint32_t batch_size)
{
	struct vector tmp;
	struct vector tmp2;

	tmp = scalar_vector_prod(layer->error_vector, -1 * training_rate / batch_size);
	free_vector(&(layer->error_vector));

	tmp2 = vector_add(layer->bias_vector_buf, tmp);
	free_vector(&(layer->bias_vector_buf));
	free_vector(&tmp);
	layer->bias_vector_buf = tmp2;

	if (layer->next_layer != NULL)
		update_bias_buffers(layer->next_layer, training_rate, batch_size);
}

void train_network (struct neuron_layer* input_layer, struct neuron_layer* output_layer, struct vector* training_inputs, struct vector* training_outputs, uint32_t num_training_examples, uint32_t batch_size, double training_rate)
{
	int i;
	int j;

	for (i = 0; i < num_training_examples; i += batch_size)
	{
		for (j = i; j < i + batch_size && j < num_training_examples; j++)
		{
			input_layer->activation_value_vector = training_inputs[j];

			simulate_network(input_layer);

			backpropagate(output_layer, training_outputs[j]);

			update_weight_buffers(input_layer->next_layer, training_rate, batch_size);
			update_bias_buffers(input_layer->next_layer, training_rate, batch_size);
		}

		flush_weights_and_biases(input_layer->next_layer);
	}
}
