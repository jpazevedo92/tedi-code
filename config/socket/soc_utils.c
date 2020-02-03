#include "soc_utils.h"

/********************** Client Side *********************/
void initClient(char *iface_name, char *srv_ip, char *clt_message){
    printf("Start socket client\n");
    int sock = 0; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0};

    //getHostandIp(iface_name, clt_message);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        //return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    /* Convert IPv4 and IPv6 addresses from text to binary form */
    if(inet_pton(AF_INET, srv_ip, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        //return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        //return -1; 
    }
    
    send(sock , clt_message , strlen(clt_message) , 0 );
    printf("Message sent\n"); 
    //read( sock , buffer, 1024); 
    //printf("%s\n",buffer );
    //printf("%s\n", clt_message);
}

/* Returns hostname for the local computer */
void checkHostName(int hostname) 
{  
    if (hostname == -1) 
    { 
        perror("gethostname"); 
        exit(1); 
    } 
} 
  
/* Returns host information corresponding to host name */
void checkHostEntry(struct hostent * hostentry) 
{ 
    if (hostentry == NULL) 
    { 
        perror("gethostbyname"); 
        exit(1); 
    } 
} 
  
/* 
    Converts space-delimited IPv4 addresses 
    to dotted-decimal format              
*/
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

    /* To retrieve hostname */
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

/********************** Server Side *********************/
void initServer(char *iface_name){
    int socket_desc , new_socket , c;
    //valread;
	char command[1024] = {0};
    char result[1024] = {0}; 
	struct sockaddr_in server , client;
	//char srv_message[100] = "";
	
	/*Create socket*/
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
	/*Prepare the sockaddr_in structure*/
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);
	
	/*Bind*/
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
		//return 1;
	}
	puts("bind done");
	
	/* Listen for incoming socket */
	listen(socket_desc , 3);
	
	/*Accept and incoming connection */
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		puts("Connection accepted");
		
		/*Reply to the client*/
		read( new_socket , command, 1024);
        printf("Command received: %s\n", command );
        execCommand(command, result);
        printf("%s\n", result );

        puts("Waiting for incoming connections...");
        //getIp(iface_name, srv_message);		
		//write(new_socket , srv_message , strlen(srv_message));
	}
	
	if (new_socket < 0)
	{
		perror("accept failed");
		//return 1;
	}
    printf("Start socket server\n");
}

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
    
    /*Put IP Address on string to send back to client*/
    sprintf(result, "Message from Socket Server on %s\n", ip_address);
}


void execCommand(char* command, char *result){
	
    printf("enter execCommand function\n");
    
    char *token; 
    token = strtok_r(command, "_", &command);
    char option = token[1];
    switch(option){
    case 'c':
    case 'C':
        execConfig(command, result);
        break;
    case 'x':
    case 'X':
		sprintf(result, "X command\n");
		break;
	 default:
		sprintf(result, "Default command\n");
		break;
	}
}

void execConfig(char* configs, char *result){
    printf("enter execConfig function\n");
    char *if_name = strtok(configs, "_");
    printf("Start configuration of %s\n", if_name);
    char *tun_ip_in = strtok(NULL, "_");
    char *tun_ip_out = strtok(NULL, "_");
    char *ip_address = strtok(NULL, "_");
    char *nw = strtok(NULL, "_");
    printf("splits all parameters\n");
    FILE *pp;
    char command_arg[1024] = {0};
    sprintf(command_arg, "cd ../../app/scripts && sh tunnel_config -a %s %s %s %s %s", if_name, tun_ip_in, tun_ip_out, ip_address, nw);
    printf("%s\n", command_arg);
    pp = popen(command_arg, "r");
    printProcessInfo(pp);
    pclose(pp);
    sprintf(result, "Configuration applied\n");
}

void printProcessInfo(FILE *pp){
    if (pp != NULL) {
        while (1) {
            char *line;
            char buf[1000];
            line = fgets(buf, sizeof buf, pp);
            if (line == NULL) break;
            if (line[0] == 'd') printf("%s", line); /* line includes '\n' */
        }
    }
}

