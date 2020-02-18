CC=gcc
CFLAGS=-Wall

SOURCE=./source
BIN=./bin

SRC=$(SOURCE)/socket.c

socket=socket
SCKT_OBJS=$(BIN)/socket.o $(BIN)/soc_utils.o

LIST=$(BIN)/socket

all: $(LIST)

$(BIN)/%: $(SCKT_OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/socket $(SCKT_OBJS)

$(BIN)/socket.o: ${SRC}
	$(CC) $(CFLAGS) -c ${SRC} -o $(BIN)/socket.o

$(BIN)/soc_utils.o: $(SOURCE)/soc_utils.c
	$(CC) $(CFLAGS) -c $(SOURCE)/soc_utils.c -o $(BIN)/soc_utils.o

clean:
	rm -rf $(SCKT_OBJS) ${LIST}

