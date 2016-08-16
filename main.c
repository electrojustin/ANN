#include <stdio.h>

#include "neuron.h"
#include "train.h"
#include "sigmoid.h"
#include "cost.h"
#include "linear.h"

void main (void)
{
	struct vector inputs [80];
	struct vector outputs [80];
	struct matrix initial_weights1;
	struct matrix initial_weights2;
	struct vector initial_bias1;
	struct vector initial_bias2;
	int i;
	struct neuron_layer* input_layer;
	struct neuron_layer* output_layer;

	inputs[0].length = 3;
	inputs[0].elements = (double*)malloc(3 * sizeof(double));
	inputs[0].elements[0] = 0.0;
	inputs[0].elements[1] = 0.0;
	inputs[0].elements[2] = 0.0; //0 0 0
	inputs[1] = copy_vector(inputs[0]);
	inputs[1].elements[0] = 1.0; //0 0 1
	inputs[2] = copy_vector(inputs[0]);
	inputs[2].elements[1] = 1.0; //0 1 0
	inputs[3] = copy_vector(inputs[2]);
	inputs[3].elements[0] = 1.0; //0 1 1
	inputs[4] = copy_vector(inputs[0]);
	inputs[4].elements[2] = 1.0; //1 0 0
	inputs[5] = copy_vector(inputs[1]);
	inputs[5].elements[2] = 1.0; //1 0 1
	inputs[6] = copy_vector(inputs[2]);
	inputs[6].elements[2] = 1.0; //1 1 0
	inputs[7] = copy_vector(inputs[3]);
	inputs[7].elements[2] = 1.0; //1 1 1

	outputs[0].length = 2;
	outputs[0].elements = (double*)malloc(2 * sizeof(double));
	outputs[0].elements[0] = 0.0;
	outputs[0].elements[0] = 0.0; //0 0
	outputs[1] = copy_vector(outputs[0]);
	outputs[1].elements[0] = 1.0; //0 1
	outputs[2] = copy_vector(outputs[1]); //0 1
	outputs[3] = copy_vector(outputs[0]);
	outputs[3].elements[1] = 1.0; //1 0
	outputs[4] = copy_vector(outputs[1]); //0 1
	outputs[5] = copy_vector(outputs[3]); //1 0
	outputs[6] = copy_vector(outputs[3]); //1 0
	outputs[7] = copy_vector(outputs[1]);
	outputs[7].elements[1] = 1.0; //1 1

	for (i = 8; i < 80; i ++)
	{
		inputs[i] = copy_vector(inputs[i % 8]);
		outputs[i] = copy_vector(outputs[i % 8]);
	}

	initial_weights2.width = 2;
	initial_weights2.height = 3;
	initial_weights2.elements = (double**)malloc(3 * sizeof(double*));
	initial_weights1.width = 3;
	initial_weights1.height = 3;
	initial_weights1.elements = (double**)malloc(3 * sizeof(double*));
	for (i = 0; i < 3; i++)
	{
		initial_weights2.elements[i] = (double*)malloc(2 * sizeof(double));
		initial_weights1.elements[i] = (double*)malloc(3 * sizeof(double));
		
		initial_weights2.elements[i][0] = 1.0;
		initial_weights2.elements[i][1] = 1.0;
		
		initial_weights1.elements[i][0] = 1.0;
		initial_weights1.elements[i][1] = 1.0;
		initial_weights1.elements[i][2] = 1.0;
	}

	initial_bias1.length = 3;
	initial_bias1.elements = (double*)malloc(3 * sizeof(double));
	initial_bias1.elements[0] = 1.0;
	initial_bias1.elements[1] = 1.0;
	initial_bias1.elements[2] = 1.0;
	initial_bias2.length = 2;
	initial_bias2.elements = (double*)malloc(2 * sizeof(double));
	initial_bias2.elements[0] = 1.0;
	initial_bias2.elements[1] = 1.0;

	activation_function = sigmoid_activation_function;
	derivative_activation_function = derivative_sigmoid_activation_function;
	cost_function = quadratic_cost_function;
	nabla_cost_function = nabla_quadratic_cost;

	input_layer = create_input_layer(3);
	output_layer = add_neuron_layer(input_layer, initial_weights1, initial_bias1);
	output_layer = add_neuron_layer(output_layer, initial_weights2, initial_bias2);

	train_network(input_layer, output_layer, inputs, outputs, 80, 8, 3.0);

	input_layer->activation_value_vector.elements = (double*)malloc(3 * sizeof(double));
	input_layer->activation_value_vector.elements[0] = 0.0;
	input_layer->activation_value_vector.elements[1] = 1.0;
	input_layer->activation_value_vector.elements[2] = 1.0;

	simulate_network(input_layer);
}
