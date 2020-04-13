/* Socket Program */

/*Header files to include */
#include "socket.h"

void chooseOption(int argc, char * argv[]){
    char option = argv[1][1];
    //char *if_name = argv[2];
    switch (option)
    {
    case 'C':
    case 'c':
        printf("UAVProtocol Client\n");
        char *srv_ip = argv[2];
        char *command = argv[3];
        printf("\tSend command %s to %s", command, srv_ip);
        initClient(srv_ip, command);
        break;
    case 'S':
    case 's':
        
        initServer();
        break;
    
    default:
        break;
    }
}

int main(int argc, char * argv[]) 
{ 
    //char option = argv[1][1];
    //char *if_name = argv[2];
    
    //printf("Option selected: %c\n", option);
    //printf("Interface Name: %s\n", if_name);
    
    chooseOption(argc, argv);

    return 0;
}