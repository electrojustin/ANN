all: error.o linear.o neuron.o backprop.o
error.o: error.h error.c
	gcc -c error.c
linear.o: error.h linear.h linear.c
	gcc -c linear.c
neuron.o: linear.h neuron.h neuron.c
	gcc -c neuron.c
backprop.o: linear.h train.h neuron.h backprop.h backprop.c
	gcc -c backprop.c
clean:
	rm error.o linear.o neuron.o backprop.o
