// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <sys/ioctl.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h>
#include <net/if.h>

#define PORT 8080

// Returns hostname for the local computer 
void checkHostName(int hostname) 
{  
    if (hostname == -1) 
    { 
        perror("gethostname"); 
        exit(1); 
    } 
} 
  
// Returns host information corresponding to host name 
void checkHostEntry(struct hostent * hostentry) 
{ 
    if (hostentry == NULL) 
    { 
        perror("gethostbyname"); 
        exit(1); 
    } 
} 
  
// Converts space-delimited IPv4 addresses 
// to dotted-decimal format 
void checkIPbuffer(char *IPbuffer) 
{ 
 
   if (NULL == IPbuffer) 
    { 
        perror("inet_ntoa"); 
        exit(1); 
    } 
}

void getHostandIp(char* iface, char *result){
    char hostbuffer[256]; 
	int hostname;

    //To retrieve hostname 
	hostname = gethostname(hostbuffer, sizeof(hostbuffer)); 
	checkHostName(hostname); 

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

    sprintf(result, "Message from: %s, on IP %s\n", hostbuffer, ip_address);
}

int main(int argc, char * argv[]) 
{ 
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char clt_message[100] = "";
    char *iface_name = argv[1];
    char *srv_ip = argv[2];  
    char buffer[1024] = {0};

    getHostandIp(iface_name, clt_message);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, srv_ip, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    }
    
    send(sock , clt_message , strlen(clt_message) , 0 );
    printf("Message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    //printf("%s\n", clt_message);

	return 0; 
}
