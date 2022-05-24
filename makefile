CC = gcc
FLAGS = -Wall -g -pthread

OBJS = stock_server.o functions.o
OBJS2 = operations_terminal.o functions.o
PROG = stock_server
PROG2 = operations_terminal

all: 	${PROG} ${PROG2} 

clean:
	rm ${OBJS} *- ${PROG}
	rm ${OBJS2} *- ${PROG2}

${PROG}:	${OBJS}
		${CC} ${FLAGS} ${OBJS} -o $@

${PROG2}:	${OBJS2}
		${CC} ${FLAGS} ${OBJS2} -o $@

.c.o:
		${CC} ${FLAGS} $< -c -o $@

######################
stock_server.o: stock_server.c functions.h
functions.o: functions.c functions.h
operations_terminal.o: operations_terminal.c functions.h


stock_server: stock_server.o
operations_terminal: operations_terminal.o
