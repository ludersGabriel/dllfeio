# variaveis
CFLAGS = -Wall
LDLIBS = 

all: client.o 
	gcc -o client.exe -s client.o -L. -lpsapi

# regra de ligacao
client.o: client.c
	gcc -c client.c -o client.o

# regras de limpeza
clean:
	-rm -f *.o

purge: clean
	-rm -f client.exe

# regras de utilização
run: all
	./client.exe