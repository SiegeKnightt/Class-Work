#/**************************
#*Reeves Farrell
#*CPSC 2310 Spring 23
#*UserName: jrfarre@clemson.edu
#*Instructor:  Dr. Yvon Feaster
#*************************/

OBJS =  driver.c functions.c
CFLAG = -Wall -g
CC = gcc
INCLUDE =
LIBS = -lm

LAB5:${OBJ}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

clean:
	-rm -f *.o LAB5 *.core

build: ${OBJS}
	${CC} ${OBJS} -o LAB5 ${LIBS}

run: build
	./LAB5