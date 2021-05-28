all:
	gcc -g tuple.c tuple_delete.c -I./ -o tupletest
clean:
	rm tupletest
