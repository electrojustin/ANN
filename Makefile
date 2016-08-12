all: error.o linear.o neuron.o
error.o: error.h error.c
	gcc -c error.c
linear.o: error.h linear.h linear.c
	gcc -c linear.c
neuron.o: linear.h neuron.h neuron.c
	gcc -c neuron.c
clean:
	rm error.o linear.o neuron.o
