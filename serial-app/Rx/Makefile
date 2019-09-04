CC=gcc
CFLAGS=-Wall
OUT=serial_rx
OBJS=serial_rx.o serialport_read.o utils.o

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

serial_rx.o: serial_rx.c serialport_read.h utils.h
	$(CC) $(CFLAGS) -c serial_rx.c -o serial_rx.o

serialport_read.o: serialport_read.c serialport_read.h
	$(CC) $(CFLAGS) -c serialport_read.c -o serialport_read.o

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c -o utils.o	

clean:
	rm -rf *.o $(OUT)
