CC=gcc
CFLAGS=-Wall

SRC=socket.c


socket=socket
SCKT_OBJS=socket.o soc_utils.o
all: socket

socket: $(SCKT_OBJS)
	$(CC) $(CFLAGS) -o $(socket) $(SCKT_OBJS)

socket.o: ${SRC}
	$(CC) $(CFLAGS) -c ${SRC} -o socket.o

soc_utils.o: soc_utils.c
	$(CC) $(CFLAGS) -c soc_utils.c -o soc_utils.o

clean:
	rm -rf *.o $(socket)

