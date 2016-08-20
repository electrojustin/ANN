CFLAGS=-Wall -Werror -O2
debug: CFLAGS=-g -Wall -Werror
debug: all
all: error.o linear.o neuron.o backprop.o train.o sigmoid.o cost.o main.o main
error.o: error.h error.c
	gcc $(CFLAGS) -c error.c
linear.o: error.h linear.h linear.c
	gcc $(CFLAGS) -c linear.c
neuron.o: linear.h neuron.h neuron.c
	gcc $(CFLAGS) -c neuron.c
backprop.o: linear.h train.h neuron.h backprop.h backprop.c
	gcc $(CFLAGS) -c backprop.c
train.o: linear.h neuron.h backprop.h train.h train.c
	gcc $(CFLAGS) -c train.c
sigmoid.o: sigmoid.h sigmoid.c
	gcc $(CFLAGS) -c sigmoid.c
cost.o: linear.h cost.h cost.c
	gcc $(CFLAGS) -c cost.c
main.o: neuron.h train.h sigmoid.h cost.h linear.h main.c
	gcc $(CFLAGS) -c main.c
main: main.o cost.o sigmoid.o train.o backprop.o neuron.o linear.o error.o
	gcc $(CFLAGS) cost.o sigmoid.o train.o backprop.o neuron.o linear.o error.o main.o -o main -lm
clean:
	rm error.o linear.o neuron.o backprop.o train.o sigmoid.o cost.o main.o
