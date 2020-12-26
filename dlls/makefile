main: mainDll.o
	gcc -o mainDll.dll -s -shared mainDll.o

mainDll.o: mainDll.c
	gcc -o mainDll.o -c mainDll.c

clean:
	-rm -f *.o

purge: clean
	-rm -f mainDll.dll