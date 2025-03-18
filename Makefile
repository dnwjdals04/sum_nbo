all: sum-nbo

sum-nbo: main.o 
	g++ -o sum-nbo main.o

main.o: main.c
	g++ -c -o main.o main.c

clean:
	rm -f sum-nbo
	rm -f *.o


