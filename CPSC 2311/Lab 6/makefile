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

LAB6:${OBJ}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

clean:
	-rm -f *.o LAB6 *.core

build: ${OBJS}
	${CC} ${OBJS} -o LAB6 ${LIBS}

run: build
	./LAB6 classdata.csv output.txt