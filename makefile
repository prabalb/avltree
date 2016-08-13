OBJS = main.o AVLTree.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

avlexec : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o avlexec

main.o : main.cpp AVLTree.cpp AVLTree.h wrapper.h
	$(CC) $(CFLAGS) main.cpp

AVLTree.o : AVLTree.cpp AVLTree.h wrapper.h
	$(CC) $(CFLAGS) AVLTree.cpp

clean:	
	\rm *.o *.gch avlexec
