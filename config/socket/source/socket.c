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
        printf("Option selected: %c\n", option);
        char *srv_ip = argv[2];
        char *command = argv[3];
        initClient(srv_ip, command);
        break;
    case 'S':
    case 's':
        printf("Option selected: %c\n", option);
        initServer();
        //initServer(if_name);
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