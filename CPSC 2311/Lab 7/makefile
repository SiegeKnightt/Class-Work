#/**************************
#*Reeves Farrell
#*CPSC 2310 Spring 23
#*UserName: jrfarre@clemson.edu
#*Instructor:  Dr. Yvon Feaster
#*************************/

OBJS =  LAB7.c
CFLAG = -Wall -g
CC = gcc
INCLUDE =
LIBS = -lm

LAB7:${OBJ}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

clean:
	-rm -f *.o LAB7 *.core

build: ${OBJS}
	${CC} ${OBJS} -o LAB7 ${LIBS}

run: build
	./LAB7