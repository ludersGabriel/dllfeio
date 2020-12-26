# variaveis
CFLAGS = -Wall
LDLIBS = 

main: main.o 
	gcc -o main.exe -s main.o

# regra de ligacao
main.o: main.c
	gcc -c main.c -o main.o

# regras de limpeza
clean:
	-rm -f *.o

purge: clean
	-rm -f main.exe

# regras de utilização
run: main
	./main.exe