
main: main.o  fake.dll
	gcc -o main.exe main.o

fake.dll: fake.o
	gcc -o fake.dll -s -shared fake.o

main.o: main.c
	gcc -c main.c -o main.o

fake.o: fakedll.c
	gcc -c fakedll.c -o fake.o

clean:
	-rm -f *.o

purge: clean
	-rm -f fake.dll
	-rm -f main.exe

run:
	./main.exe