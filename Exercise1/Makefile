#
# Makefile
#
# Databases on modern CPU architectures 
# Exercise 1
#

CC = g++
CFLAGS = -Wall -O1 -g -std=c++11
BINPATH = ../bin/

all: test gen

test: test.o external_sort.o
	$(CC) -o ../bin/test test.o external_sort.o

gen: gen.o
	$(CC) -o ../bin/gen gen.o

test.o: test.cpp
	$(CC) $(CFLAGS) -o test.o -c test.cpp

gen.o: gen.cpp
	$(CC) $(CFLAGS) -o gen.o -c gen.cpp

external_sort.o: external_sort.cpp external_sort.hpp
	$(CC) $(CFLAGS) -o external_sort.o -c external_sort.cpp

clean:
	rm -f $(BINPATH)/test $(BINPATH)//gen *.o

# scheduler-shell: scheduler-shell.o proc-common.o
# 	$(CC) -o scheduler-shell scheduler-shell.o proc-common.o

# scheduler-shell-h-l: scheduler-shell-h-l.o proc-common.o
# 	$(CC) -o scheduler-shell-h-l scheduler-shell-h-l.o proc-common.o

# shell: shell.o proc-common.o
# 	$(CC) -o shell shell.o proc-common.o

# prog: prog.o proc-common.o
# 	$(CC) -o prog prog.o proc-common.o

# execve-example: execve-example.o 
# 	$(CC) -o execve-example execve-example.o

# proc-common.o: proc-common.c proc-common.h
# 	$(CC) $(CFLAGS) -o proc-common.o -c proc-common.c

# shell.o: shell.c proc-common.h request.h
# 	$(CC) $(CFLAGS) -o shell.o -c shell.c

# scheduler.o: scheduler.c proc-common.h request.h
# 	$(CC) $(CFLAGS) -o scheduler.o -c scheduler.c

# scheduler-shell.o: scheduler-shell.c proc-common.h request.h
# 	$(CC) $(CFLAGS) -o scheduler-shell.o -c scheduler-shell.c

# scheduler-shell-h-l.o: scheduler-shell-h-l.c proc-common.h request.h
# 	$(CC) $(CFLAGS) -o scheduler-shell-h-l.o -c scheduler-shell-h-l.c

# prog.o: prog.c
# 	$(CC) $(CFLAGS) -o prog.o -c prog.c

# execve-example.o: execve-example.c
# 	$(CC) $(CFLAGS) -o execve-example.o -c execve-example.c