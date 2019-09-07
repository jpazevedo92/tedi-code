CC=gcc
CFLAGS=-Wall

server=app_test_srv
client=app_test_clt
SRV_OBJS=server.o
CLT_OBJS=client.o

$(server): $(SRV_OBJS)
	$(CC) $(CFLAGS) -o $(server) $(SRV_OBJS)

$(client): $(CLT_OBJS)
	$(CC) $(CFLAGS) -o $(client) $(CLT_OBJS)

server.o: server.c
	$(CC) $(CFLAGS) -c server.c -o server.o

client.o: client.c
	$(CC) $(CFLAGS) -c client.c -o client.o

all: $(SRV_OBJS) $(CLT_OBJS)
	$(CC) $(CFLAGS) -o $(server) $(SRV_OBJS)
	$(CC) $(CFLAGS) -o $(client) $(CLT_OBJS)
clean:
	rm -rf *.o $(OUT)
