#include "soc_utils.h"

/********************** Client Side *********************/
void initClient(char *srv_ip, char *clt_message)
{
    printf("Start socket client\n");
    int sockfd; 
    char buffer[MAXLINE]; 
    struct sockaddr_in     servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT1); 
    servaddr.sin_addr.s_addr = inet_addr(srv_ip); 
      
    sendto(sockfd, (const char *)clt_message, strlen(clt_message), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 

    close(sockfd); 
   
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
//void initServer(char *iface_name)
void initServer(){
    int sockfd; 
    char command[MAXLINE]; 
    char result[MAXLINE];

    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    puts("Waiting for incoming connections...");
    
    while(1)
    {
        int len, n; 
        len = sizeof(cliaddr);  //len is value/resuslt 
        n = recvfrom(sockfd, (char *)command, MAXLINE,  
            MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
            &len); 
        command[n] = '\0'; 
        printf("Command received: %s\n", command);
        execCommand(command, result);
        printf("Command Result: %s\n", result);
        sendto(sockfd, (const char *)result, strlen(result),  
              MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
              len);
        printf("Command Result Sent: %s\n", result);

        //Wait for new connection
        puts("Waiting for incoming connections...");
    }
    printf("Start socket server\n");
}

// void getIp(char* iface, char *result){

//     unsigned char ip_address[15];
//     int fd;
//     struct ifreq ifr;
     
//     /*AF_INET - to define network interface IPv4*/
//     /*Creating soket for it.*/
//     fd = socket(AF_INET, SOCK_DGRAM, 0);
     
//     /*AF_INET - to define IPv4 Address type.*/
//     ifr.ifr_addr.sa_family = AF_INET;
     
//     /*eth0 - define the ifr_name - port name
//     where network attached.*/
//     memcpy(ifr.ifr_name, iface , IFNAMSIZ-1);
     
//     /*Accessing network interface information by
//     passing address using ioctl.*/
//     ioctl(fd, SIOCGIFADDR, &ifr);
//     /*closing fd*/
//     close(fd);
     
//     /*Extract IP Address*/
//     strcpy(ip_address,inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    
//     /*Put IP Address on string to send back to client*/
//     sprintf(result, "Message from Socket Server on %s\n", ip_address);
// }

void execCommand(char* command, char *result){
	
    printf("enter execCommand function\n");
    
    char *token; 
    token = strtok_r(command, "_", &command);
    char option = token[1];
    switch(option){
        case 'a':
        case 'A':
            execAliveCheck(result);
            //execConfig(command, result);
            break;
        case 't':
        case 'T':
            execConfigTun(command, result);
            break;
        case 'm':
        case 'M':
            sprintf(result, "MPLS command\n");
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

void execConfigTun(char* configs, char *result){
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
    sprintf(result, "Configuration of %s is OK", if_name);
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


void execAliveCheck(char *result){
    sprintf(result, "OK");
}