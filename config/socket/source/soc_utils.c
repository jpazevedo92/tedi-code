#include "soc_utils.h"

/*
    Client init function 
*/
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

void initUAVClient(char *srv_ip, char *clt_message, char *result)
{
    printf("Start socket client\n");
    int sockfd; 
    struct sockaddr_in     servaddr; 
    int n, len;

    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr(srv_ip); 
      
    sendto(sockfd, (const char *)clt_message, strlen(clt_message), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 

    n = recvfrom(sockfd, (char *)result, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len); 
    result[n] = '\0'; 
    close(sockfd); 
   
}

/*
    Server init function 
*/
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
        //exit(EXIT_FAILURE); 
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

/*
    Protocol Command functions
*/

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
        case 'i':
        case 'I':
            execInitFirmware(command, result);
            break;
        case 'm':
        case 'M':
            sprintf(result, "MPLS command\n");
            break;
        case 'p':
        case 'P':
            execConfigIpTables(command, result);
            break;
        case 'r':
        case 'R':
            execConfigRoute(command, result);
            break;
        case 's':
        case 'S':
            setUAVTunnel(command, result);
            break;
        case 't':
        case 'T':
            execConfigTun(command, result);
            break;
        case 'u':
        case 'U':
            execUavTun(command, result);
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
    sprintf(command_arg, "cd ../../../app/scripts && sh tunnel_config -a %s %s %s %s %s", if_name, tun_ip_in, tun_ip_out, ip_address, nw);
    printf("%s\n", command_arg);
    pp = popen(command_arg, "r");
    printProcessInfo(pp);
    pclose(pp);
    sprintf(result, "Configuration of %s is OK", if_name);
}

void execAliveCheck(char *result){
    sprintf(result, "OK");
}

void execInitFirmware(char* configs, char *result){
    char id = configs[0];
    char *s = {0};
    printf("ID Received %c\n", id);
    FILE *pp;
    char command_arg[1024] = {0};
    printf("current dir: %s\n", getcwd(s, 100)); 
    sprintf(command_arg, "cd ../../../app/scripts/ && sh start_firmware %c", id);
    printf("%s\n", command_arg);
    pp = popen(command_arg, "r");
    printProcessInfo(pp);
    pclose(pp);
    sprintf(result, "Firmware Ready");
}

void execUavTun(char* configs, char *result){
    sprintf(result, "-A");
}

void execConfigRoute(char* configs, char *result){
    printf("enter execConfig function\n");
    char *if_name = strtok(configs, "_");
    printf("Route configuration of %s\n", if_name);
    char *tun_network = strtok(NULL, "_");
    char *tun_ip = strtok(NULL, "_");
    FILE *pp;
    char command_arg[1024] = {0};
    sprintf(command_arg, "cd ../../../app/scripts && sh route_config -a %s %s %s", if_name, tun_network, tun_ip);
    printf("%s\n", command_arg);
    pp = popen(command_arg, "r");
    printProcessInfo(pp);
    pclose(pp);
    sprintf(result, "Route configuration of %s is OK", if_name);
}

void execConfigIpTables(char* configs, char *result){
    printf("enter execConfig function\n");
    char *if_name1 = strtok(configs, "_");
    char *if_name2 = strtok(configs, "_");
    printf("Start configuration of %s\n", if_name1);
    FILE *pp;
    char command_arg[1024] = {0};
    sprintf(command_arg, "cd ../../../app/scripts && sh route_config -t %s %s", if_name1, if_name2);
    printf("%s\n", command_arg);
    pp = popen(command_arg, "r");
    printProcessInfo(pp);
    pclose(pp);
    sprintf(result, "IP Tables Configuration of %s is OK", if_name1);
}

void setUAVTunnel(char* configs, char *result){
    char *command_local = configs; 
    char *command_remote = {0};
    /*char msg[MAXLINE] = {0};
    char res[MAXLINE] = {0};
    char res1[MAXLINE] = {0};
    char res2[MAXLINE] = {0};
    char res3[MAXLINE] = {0};
    char res4[MAXLINE] = {0}; */   
    command_remote = strtok_r(command_local, " ", &command_local);
/*     printf("Local: %s Remote: %s\n", command_local, command_remote);
    sprintf(msg, "-T_%s", command_remote); */
    
    char* tun_name = strtok(command_remote, "_");
/*     char* remote_ip = strtok(NULL, "_");
    printf("Remote IP: %s\n", remote_ip);

    initUAVClient(remote_ip, msg, res);
    char compare_string[MAXLINE] = {0};
    sprintf(compare_string, "Configuration of %s is OK", tun_name);
    int condition = strcmp(res, compare_string);
    printf("%s %d\n", res ,condition);
    if(condition == STR_EQUAL)
        execConfigTun(command_local, res1);

    int condition2 = strcmp(res, res1);
    printf("%d\n", condition2); */

    /* Well */

    int n = tun_name[strlen(tun_name)-1] - '0';
    char route_command[MAXLINE]; 
    for(int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            /* First network node */
            printf("Send command to base");
            char r_command2[MAXLINE] = "-R_";
            char route_command2[MAXLINE];
            char base_ip[MAXLINE];
            sprintf(base_ip, "10.0.%d0.1", n);
            getCommand(tun_name, route_command2, True);
            printf("Command %s", route_command2);
            //strcat(r_command2, route_command2);
            //initUAVClient(base_ip, r_command2, res2);
            //execConfigRoute(route_command, res2);
        } else
        {
            /* Intermedious nodes */
            char route_command3[MAXLINE];
            char tun_input[MAXLINE];
            getSimpleTunnelName(tun_name, tun_input);
            sprintf(route_command3, "-P_%s_%s", tun_input, tun_name);
            //initUAVClient(remote_ip, route_command3, res2);
            //execConfigIpTables(route_command3, res3);

        }
    }
    getCommand(tun_name, route_command, False);
    //execConfigRoute(route_command, res4);

/*     if(condition2 == STR_EQUAL)
        sprintf(result, "%s configuration applied", tun_name); */

}

/*
    Auxiliar functions
*/

void printProcessInfo(FILE *pp){
    //printf("printProcessInfo\n");
    if (pp != NULL) {
        //printf("printProcessInfo: if pp != null\n ");
        while (1) {
            //printf("printProcessInfo: while(1)\n ");
            char *line;
            char buf[1000];
            line = fgets(buf, sizeof buf, pp);
            //printf("printProcessInfo: line: %s\n ");
            if (line == NULL) break;
            printf("%s", line); /* line includes '\n' */
        }
    }
}

void getCommand(char* iface, char *result, int option){
    char sTunName[MAXLINE];
    if(option)
        getSimpleTunnelName(iface, sTunName/* , False */);
    else if(!option)
        sprintf(sTunName, "$s", iface);
    else
        sprintf(sTunName, "invalid iface");    
    char net_ip[MAXLINE];
    getIfIp(sTunName, net_ip);
    char net_address[MAXLINE];
    getNetworkInfo(sTunName, ADDRESS, net_address);
    char net_mask[MAXLINE];
    getNetworkInfo(sTunName, MASK, net_address);
    char network[MAXLINE];
    sprintf(network, "%s%s", net_address, net_mask);
    sprintf(result, "%s_%s_%s", sTunName, network, net_ip);

}

void getIfIp(char* iface, char *result){
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1) 
    {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }


    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) 
    {
        if (ifa->ifa_addr == NULL)
            continue;  

        s=getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in),host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

        if((strcmp(ifa->ifa_name, iface)==0)&&(ifa->ifa_addr->sa_family==AF_INET))
        {
            if (s != 0)
            {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
            }
            printf("\t  Address : <%s>\n", host);

            sprintf(result, "%s", host); 
        }
    }

    freeifaddrs(ifaddr);
}

void getSimpleTunnelName(char *str, char* result/* , int inc */)
{
    for(int i = 0; i < sizeof(str)-2; i++){   
        /* if(inc == False) */
            result[i] = str[i];
/*         if(inc == True && i == strlen(str)-3);
            result[i] = (char)((int)(str[i]-'0')); */
    }
}

void getNetworkInfo(char *iface, int option, char *result){
    struct ifaddrs *id;
    int val;
    char net_address[1024];
    char net_mask[1024];
    val = getifaddrs (&id);
    if(strcmp(id->ifa_name, iface) == 0)
        switch (option)
        {
        case ADDRESS:
            print_ip(id->ifa_data, net_address);
            sprintf(result, "%s", net_address);
            break;
        case MASK: 
            print_ip(id->ifa_netmask, net_mask);
            char plNetmask[1024];
            getMaskPrefixLength(net_mask, plNetmask);
            break;
        default:
            sprintf(result, "getNetoworkInfo: option not correct");
            break;
        }
    else
    {
       sprintf(result, "getNetoworkInfo: the selected interface not exist");     
    }
    
}

void print_ip(unsigned int ip, char *result)
{
  unsigned char bytes[4];
  bytes[0] = ip & 0xFF;
  bytes[1] = (ip >> 8) & 0xFF;
  bytes[2] = (ip >> 16) & 0xFF;
  bytes[3] = (ip >> 24) & 0xFF;
  sprintf (result, "%d.%d.%d.%d", bytes[3], bytes[2], bytes[1], bytes[0]);
}

void getMaskPrefixLength(char *mask, char *result){
    //const char *network = "255.255.255.0";
    int n;
    inet_pton(AF_INET, mask, &n);
    int i = 0;

    while (n > 0) {
            n = n >> 1;
            i++;
    }
    sprintf(result, "/%d", i);

}