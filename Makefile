CC = gcc
CFLAGS = -Wall -c
OBJS = mapas.o

all: jogador1 jogador2

mapas.o: mapas.c mapas.h
	$(CC) $(CFLAGS) mapas.c

jogador1.o: jogador1.c mapas.h
	$(CC) $(CFLAGS) jogador1.c

jogador2.o: jogador2.c mapas.h
	$(CC) $(CFLAGS) jogador2.c

jogador1: jogador1.o $(OBJS)
	$(CC) -o jogador1 jogador1.o $(OBJS)

jogador2: jogador2.o $(OBJS)
	$(CC) -o jogador2 jogador2.o $(OBJS)

clean limpar:
	rm -f jogador1 jogador2 *.o *~
	echo "Limpeza concluída."
