#include <stdint.h>

#include "linear.h"

#ifndef NEURON_H
#define NEURON_H
struct neuron_layer
{
	struct neuron_layer* next_layer;
	struct neuron_layer* prev_layer;
	struct matrix weight_matrix;
	struct matrix weight_matrix_buf;
	struct vector bias_vector;
	struct vector bias_vector_buf;
	struct vector z_value_vector;
	struct vector activation_value_vector;
	struct vector error_vector;
};

double (*activation_function)(double);
double (*derivative_activation_function)(double);

struct neuron_layer* create_input_layer (uint32_t size);

struct neuron_layer* add_neuron_layer (struct neuron_layer* prev_layer, struct matrix weight_matrix, struct vector bias_vector);

void free_network (struct neuron_layer* to_free);

struct vector simulate_network (struct neuron_layer* input_layer);
#endif
