prog: Countries.o HashTable.o KeyValuePair.o LinkedList.o Main.o
	gcc Countries.o HashTable.o KeyValuePair.o LinkedList.o Main.o -o prog

Countries.o: Countries.c Countries.h HashTable.h Defs.h LinkedList.h KeyValuePair.h
	gcc -c Countries.c

HashTable.o: HashTable.c HashTable.h Defs.h KeyValuePair.h LinkedList.h
	gcc -c HashTable.c

KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c

LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c

Main.o: Main.c KeyValuePair.h Defs.h Countries.h HashTable.h LinkedList.h
	gcc -c Main.c

clean: 
	rm -f Countries.o HashTable.o KeyValuePair.o LinkedList.o Main.o prog
