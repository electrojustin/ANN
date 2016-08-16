all: error.o linear.o neuron.o backprop.o train.o sigmoid.o cost.o main.o main
error.o: error.h error.c
	gcc -c error.c
linear.o: error.h linear.h linear.c
	gcc -c linear.c
neuron.o: linear.h neuron.h neuron.c
	gcc -c neuron.c
backprop.o: linear.h train.h neuron.h backprop.h backprop.c
	gcc -c backprop.c
train.o: linear.h neuron.h backprop.h train.h train.c
	gcc -c train.c
sigmoid.o: sigmoid.h sigmoid.c
	gcc -c sigmoid.c
cost.o: linear.h cost.h cost.c
	gcc -c cost.c
main.o: neuron.h train.h sigmoid.h cost.h linear.h
	gcc -c main.c
main: main.o cost.o sigmoid.o train.o backprop.o neuron.o linear.o error.o
	gcc cost.o sigmoid.o train.o backprop.o neuron.o linear.o error.o main.o -o main
clean:
	rm error.o linear.o neuron.o backprop.o train.o sigmoid.o cost.o main.o
