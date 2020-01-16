CC=gcc
CFLAGS=-Wall


socket=message_socket

SCKT_OBJS=socket.o

$(socket): $(SRV_OBJS)
	$(CC) $(CFLAGS) -o $(socket) $(SCKT_OBJS)

socket.o: socket.c socket.h
	$(CC) $(CFLAGS) -c socket.c socket.h -o socket.o

all: $(SCKT_OBJS)
	$(CC) $(CFLAGS) -o $(socket) $(SCKT_OBJS)

clean:
	rm -rf *.o $(socket)
