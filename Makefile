CFLAGS = -Wall 

obj = myavl.o libBst.o libAvl.o

all: myavl

myavl: ${obj}

myavl.o: myavl.c libBst.h libAvl.h
	gcc ${CFLAGS} -c myavl.c
libBst.o: libBst.c libBst.h libAvl.h libAvl.c
	gcc ${CFLAGS} -c libBst.c
libAvl.o: libAvl.c libAvl.h libBst.h libBst.c
	gcc ${CFLAGS} -c libAvl.c

clean:
	rm -f myavl ${obj} *~

purge: clean
	rm -f myavl

