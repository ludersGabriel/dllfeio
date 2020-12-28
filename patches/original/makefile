
main: main.o  main.dll
	gcc -o main.exe main.o

main.dll: maindll.o
	gcc -o maindll.dll -s -shared maindll.o

main.o: main.c
	gcc -c main.c -o main.o

maindll.o: maindll.c
	gcc -c maindll.c -o maindll.o

clean:
	-rm -f *.o

purge: clean
	-rm -f maindll.dll
	-rm -f main.exe

run:
	./main.exe