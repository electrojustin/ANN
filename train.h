#include "linear.h"

#ifndef TRAIN_H
#define TRAIN_H
double (*cost_function)(struct vector, struct vector);

struct vector (*nabla_cost_function)(struct vector, struct vector);

void train_network (struct neuron_layer* input_layer, struct neuron_layer* output_layer, struct vector* training_inputs, struct vector* training_outputs, uint32_t num_training_examples, uint32_t batch_size, double training_rate);
#endif
