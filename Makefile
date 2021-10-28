objects =   treap.o main.o

all :   $(objects)
	gcc -o  alg $(objects)

run :   alg
	./alg

treap.o :   treap.h
main.o  :   treap.h

clean   :
	rm *.o alg
