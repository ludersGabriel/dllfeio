# variaveis
CFLAGS = -Wall
LDLIBS = 
OBJ = add_basic.o client.o


all: client.o add_basic.dll
	gcc -o client.exe -s client.o -L. -ladd_basic


# regra de ligacao
client.o: add_client.c
	gcc -c add_client.c -o client.o

add_basic.o: add_basics.c
	gcc -c add_basics.c -o add_basic.o


# regras de compilacao
add_basic.dll: add_basic.o
	gcc -o add_basic.dll -s -shared add_basic.o


# regras de limpeza
clean:
	-rm -f *.o

purge: clean
	-rm -f client.exe
	-rm -f add_basic.dll


# regras de utilização
run: all
	./client.exe