# variaveis
CFLAGS = -Wall
LDLIBS = 

main: main.o utils.o
	gcc -o main.exe -s main.o utils.o

# regra de ligacao
main.o: main.c
	gcc -c main.c -o main.o

utils.o: utils.c
	gcc -c utils.c -o utils.o

# regras de limpeza
clean:
	-rm -f *.o

purge: clean
	-rm -f main.exe

# regras de utilização
run: main
	./main.exe