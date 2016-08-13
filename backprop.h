#include "linear.h"
#include "neuron.h"

#ifndef BACKPROP_H
#define BACKPROP_H
void backpropagate (struct neuron_layer* output_layer, struct vector training_output);
#endif
