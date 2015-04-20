#
# Makefile
#
# Databases on modern CPU architectures 
#

CC = g++
CFLAGS = -Wall -O1 -g

all: 
	cd Exercise1; make


clean:
	cd Exercise1; make clean

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