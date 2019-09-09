
// Server side C/C++ program to demonstrate Socket programming 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <sys/ioctl.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>	//inet_addr
#include <string.h>
#include <net/if.h>

#define PORT 8080

void getIp(char* iface, char *result){

    unsigned char ip_address[15];
    int fd;
    struct ifreq ifr;
     
    /*AF_INET - to define network interface IPv4*/
    /*Creating soket for it.*/
    fd = socket(AF_INET, SOCK_DGRAM, 0);
     
    /*AF_INET - to define IPv4 Address type.*/
    ifr.ifr_addr.sa_family = AF_INET;
     
    /*eth0 - define the ifr_name - port name
    where network attached.*/
    memcpy(ifr.ifr_name, iface , IFNAMSIZ-1);
     
    /*Accessing network interface information by
    passing address using ioctl.*/
    ioctl(fd, SIOCGIFADDR, &ifr);
    /*closing fd*/
    close(fd);
     
    /*Extract IP Address*/
    strcpy(ip_address,inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
     
    //printf("System IP Address is: %s\n",ip_address);

    sprintf(result, "Message from Socket Server on %s\n", ip_address);
}


int main(int argc, char const *argv[]) 
{
	int socket_desc , new_socket , c, valread;
	char buffer[1024] = {0}; 
	struct sockaddr_in server , client;
	char *iface_name = argv[1];
	char srv_message[100] = "";
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
		while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		puts("Connection accepted");
		
		//Reply to the client
		valread = read( new_socket , buffer, 1024); 
		printf("%s\n",buffer ); 
		getIp(iface_name, srv_message);
		//message = "Hello Client , I have received your connection. But I have to go now, bye\n";
		write(new_socket , srv_message , strlen(srv_message));
	}
	
	if (new_socket < 0)
	{
		perror("accept failed");
		return 1;
	}
	
	return 0;
} 
