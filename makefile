astar: main.o genetic.o
	icc -prof-gen=srcpos -o ga main.o genetic.o -g -fopenmp 

main.o: main.c
	icc -prof-gen=srcpos -c main.c -g -lm -g -fopenmp
genetic.o: genetic.c
	icc -prof-gen=srcpos -c genetic.c -g -lm -g -fopenmp

clean:
	rm *.o
	rm ga

