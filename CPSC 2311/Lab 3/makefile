OBJS =  driver.c functions.c
CFLAG = -Wall -g
CC = gcc
INCLUDE =
LIBS = -lm

LAB3:${OBJ}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

clean:
	-rm -f *.o LAB3 *.core

run:
	./LAB3