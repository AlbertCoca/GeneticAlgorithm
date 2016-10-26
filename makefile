astar: main.o genetic.o
	gcc -o ga main.o genetic.o

main.o: main.c
	gcc -c main.c -g -lm
genetic.o: genetic.c
	gcc -c genetic.c -g -lm

clean:
	rm *.o
