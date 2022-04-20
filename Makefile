CC=gcc
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS=-Wall -Wextra

#procA
procA: procA.o
	${CC} ${CFLAGS} ${CFLAGS_DBG} procA.o -o procA

procA.o: procA.c
	${CC} ${CFLAGS} ${CFLAGS_DBG} -c procA.c

#procB
procB: procB.o
	${CC} ${CFLAGS} ${CFLAGS_DBG} procB.o -o procB

procB.o: procB.c
	${CC} ${CFLAGS} ${CFLAGS_DBG} -c procB.c

clean:
	rm *.o procA procB

#make procA, make procB