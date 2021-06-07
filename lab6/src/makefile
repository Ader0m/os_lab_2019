CC=gcc
CFLAG=-I.

all : server client

server :
	$(CC) server.c modul.c modul.h -lpthread -o server $(CFLAG)

client : 
	$(CC) client.c modul.c modul.h -lpthread -o client $(CFLAG)

clean :
	rm server client