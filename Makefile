all: tuple

tuple_delete.o: tuple_delete.c tuple.h
	gcc -O -c tuple_delete.c -I./

tuple.o: tuple.c tuple.h
	gcc -O -c tuple.c -I./

tuple: tuple.o tuple_delete.o
	ar rcs libtuple.a tuple.o tuple_delete.o

clean:
	rm libtuple.a *.o *.gch
