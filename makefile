CC = gcc
FLAGS = -Wall -g -pthread
OBJS = main.o functions.o
PROG = main

all: 	${PROG}

clean:
	rm ${OBJS} *- ${PROG}

${PROG}:	${OBJS}
		${CC} ${FLAGS} ${OBJS} -o $@

.c.o:
		${CC} ${FLAGS} $< -c -o $@

######################
main.o: main.c functions.h
functions.o: functions.c functions.h
main: main.o functions.o
