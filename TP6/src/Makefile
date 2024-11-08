CC ?= gcc

CFLAGS = -Wall -Wextra -ggdb3

COBJS ?= client.o bmp.o couleur.o cJSON.o
SOBJS ?= serveur.o operator.o cJSON.o

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SOBJS)
	$(CC) $(CFLAGS) -o $(SERVER) $(SOBJS) -lm

$(CLIENT): $(COBJS)
	$(CC) $(CFLAGS) -o $(CLIENT) $(COBJS)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

