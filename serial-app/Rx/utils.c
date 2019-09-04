#include "utils.h"

void get_commands_array(char *str_rcvd, char *cmd_array[][COLUMNS]){
	char *token;
	char *commands;
	strtok_r(str_rcvd, "|", &commands);
	int n_uavs = atoi(str_rcvd);
	int array_size = 2*n_uavs;
	char *strs_rcvd[array_size];		
	//sprintf("N_UAVS: %s Commands: %s\n", str_rcvd, commands);
	int i = 0;
	while ((token = strtok_r(commands, "_", &commands))){
		strs_rcvd[i]=token;
		i++;
	}

	for(i=0; i<array_size; i++){
		if(i==0){
			cmd_array[i][0] = strs_rcvd[i];
			cmd_array[i][1] = strs_rcvd[i+1];
		} else {
			cmd_array[i][0] = strs_rcvd[i+i];
			cmd_array[i][1] = strs_rcvd[i+i+1];
		}
	}
	
	for(int i = 0; i< n_uavs; i++){
		for(int j=0; j<2; j++)
			 printf("cmd_array[%d][%d] = %s\n", i,j, cmd_array[i][j] );
	}
	//return cmd_array;
}

int get_n_uavs(char *str_rcvd){
		char *commands;
		strtok_r(str_rcvd, "|", &commands);
		int n_uavs = atoi(str_rcvd);
		
		return n_uavs;
}
