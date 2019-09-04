#ifndef SERIALPORT_READ_H_
#define SERIALPORT_READ_H_

#include <stdio.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */ 
#include <errno.h>   /* ERROR Number Definitions           */

int connect_serial_port();
void receive_serial_message(int fd, char *read_buffer);

#endif
