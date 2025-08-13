# Name: Sushrut Chandra
# cmscs 216

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -fstack-protector-all -Werror

all: test1.x test2.x 

prio-q.o: prio-q.c prio-q.h prio-q-datastructure.h
	$(CC) $(CFLAGS) -c prio-q.c

test1.x: test1.o prio-q.o 
	$(CC) test1.o prio-q.o -o test1.x

test2.x: test2.o prio-q.o 
	$(CC) test2.o prio-q.o -o test2.x

clean:
	rm -f test*.x test*.o prio-q.o
