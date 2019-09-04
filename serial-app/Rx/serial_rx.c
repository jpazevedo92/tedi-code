#include "serialport_read.h"
#include "utils.h"

int main(void)
{
	char message_received[100]="";
	char message_received_temp[100]="";
	int fd = connect_serial_port();
	while(1){
		receive_serial_message(fd, message_received);
		strcpy(message_received_temp, message_received);
		int n_uavs = get_n_uavs(message_received_temp);
		char *cmd_array[n_uavs][COLUMNS];
		get_commands_array(message_received, cmd_array);
		
	}	

	close(fd); /* Close the serial port */
	return 0;
}
