CC=gcc
CFLAGS=-Wall

server=message_srv
client=message_clt
server_test=app_test_srv
client_test=app_test_clt
SRV_OBJS=server.o
CLT_OBJS=client.o

$(server): $(SRV_OBJS)
	$(CC) $(CFLAGS) -o $(server) $(SRV_OBJS)

$(client): $(CLT_OBJS)
	$(CC) $(CFLAGS) -o $(client) $(CLT_OBJS)

$(server_test): $(SRV_OBJS)
	$(CC) $(CFLAGS) -o $(server_test) $(SRV_OBJS)

$(client_test): $(CLT_OBJS)
	$(CC) $(CFLAGS) -o $(client_test) $(CLT_OBJS)

server.o: server.c
	$(CC) $(CFLAGS) -c server.c -o server.o

client.o: client.c
	$(CC) $(CFLAGS) -c client.c -o client.o

all: $(SRV_OBJS) $(CLT_OBJS)
	$(CC) $(CFLAGS) -o $(server) $(SRV_OBJS)
	$(CC) $(CFLAGS) -o $(client) $(CLT_OBJS)
	$(CC) $(CFLAGS) -o $(server_test) $(SRV_OBJS)
	$(CC) $(CFLAGS) -o $(client_test) $(CLT_OBJS)


clean:
	rm -rf *.o $(server) $(client) $(server_test) $(client_test) server client
