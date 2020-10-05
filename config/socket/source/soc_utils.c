#include "soc_utils.h"

/*
    Client init function 
*/
void initClient(char *srv_ip, char *clt_message)
{
    int sockfd; 
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
    printf("UAVProtocol Client\n");
    printf("\tSend command %s to %s\n", clt_message, srv_ip);

    int sockfd; 
    struct sockaddr_in     servaddr; 
    int n;
    socklen_t len;

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

void initUavMplsClient(char *srv_ip, char *clt_message, char *result)
{
    printf("UAVProtocol Client\n");
    printf("\tSend command %s to %s\n", clt_message, srv_ip);

    int sockfd; 
    struct sockaddr_in     servaddr; 

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
    close(sockfd);  
   
}
/*
    Server init function 
*/
void initServer(){
    int sockfd; 
    char command[MAXLINE]; 
    char result[MAXLINE];
    socklen_t len;
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
    
    printf("UAVProtocol Server:\n\tWaiting for new commands\n");
    
    while(1)
    {
        int n;

        len = sizeof(cliaddr);  //len is value/resuslt 
        n = recvfrom(sockfd, (char *)command, MAXLINE,  
            MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
            &len); 
        command[n] = '\0'; 
        printf("Command received: %s\n", command);
        execCommand(command, result);
        sendto(sockfd, (const char *)result, strlen(result),  
              MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
              len);
        printf("Response to command %s: %s\n", command,result);

        //Wait for new connection
        printf("UAVProtocol Server:\n\tWaiting for new commands\n");
    }
}

/*
    Protocol Command functions
*/

void execCommand(char* command, char *result){
    printf("\tEnter execCommand\n");
    char *token;
    if(command[2] != '_'){
         token = strtok_r(command, "\'", &command);
    } else
     {
        token = strtok_r(command, "_", &command);
     }
    char option = token[1];
    printf("\tOption %c\n", option);
    
    switch(option){
	 
        case 'a':
        case 'A':
            printf("\tEnter execCommand: 'A' option\n");
            execAliveCheck(result);
            break;
        case 'd':
        case 'D':
            setRouteDown(command, result);
            break;
        case 'i':
        case 'I':
            execInitFirmware(command, result);
            break;
        case 'm':
        case 'M':
            printf("\tIncomnig args: %s\n", command);
            execConfigMPLS(command, result);
            break;
        case 'n':
        case 'N':
            execAddMPLSRoute(command, result);
            break;
        case 'o':
        case 'O':
            setLinkDown(command, result);
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
        // case 'x':
        // case 'X':
        //     sprintf(result, "X command\n");
        //     break;
         default:
             sprintf(result, "Default command\n");
             break;
	}
}

void execAliveCheck(char *result){
    printf("\t\tAlive Check Command\n");
    sprintf(result, "OK");
}

void execConfigTun(char* configs, char *result){
    printf("\tenter execConfigTun\n ");
    printf("\texecConfigTun configs: %s\n", configs);
    char *if_name = strtok(configs, "_");
    printf("Start configuration of %s\n", if_name);
    char *tun_ip_in = strtok(NULL, "_");
    char *tun_ip_out = strtok(NULL, "_");
    char *ip_address = strtok(NULL, "_");
    char *nw = strtok(NULL, "_");

    FILE *pp;
    char command_arg[1024] = {0};
    sprintf(command_arg, "cd ../../../app/scripts && sh tunnel_config -a %s %s %s %s %s", if_name, tun_ip_in, tun_ip_out, ip_address, nw);
    printf("%s\n", command_arg);
    pp = popen(command_arg, "r");
    printProcessInfo(pp);
    pclose(pp);
    sprintf(result, "Configuration of %s is OK", if_name);
}

void execConfigMPLS(char* configs, char *result){
    printf("\tEnter execConfigMPLS\n");
    printf("\tIncomnig args: %s\n", configs);
    char *token; 
    token = strtok_r(configs, "_", &configs);

    char option = token[0];

    char *if_name = strtok(configs, "_");
    printf("\tSplit args: \n\t\tOption: %c\n\t\t Interface Name: %s\n\n", option, if_name);
    FILE *pp;
    char command_arg[1024] = {0};
    printf("Start MPLS configuration of %s\n", if_name);

    char  *nw, *label_out, *label_out_local, *label_in, *ip_out;
 
    switch (option)
    {
        
        case 'a':
        case 'A':
            nw = strtok(NULL, "_");
            label_out = strtok(NULL, "_");
            /*
            Add MLPLS to network
            */
            memset(command_arg, 0, sizeof(command_arg));
            sprintf(command_arg, "cd ../../../app/scripts && sh mpls_config -a %s %s %s", if_name, nw, label_out);
            printf("%s\n", command_arg);
            sprintf(result, "MPLS configuration of %s is OK", if_name);
            pp = popen(command_arg, "r");
            printProcessInfo(pp);
            pclose(pp);
            break;
        case 'c':
        case 'C':

            /*
            Enable ifaces
            */

            sprintf(command_arg, "cd ../../../app/scripts && sh mpls_config -c %s", if_name);
            printf("%s\n", command_arg);

            pp = popen(command_arg, "r");
            printProcessInfo(pp);
            pclose(pp);
            break;
        case 'd':
        case 'D':
            nw = strtok(NULL, "_");
            label_out = strtok(NULL, "_");
            /*
            Add MLPLS to network
            */
            memset(command_arg, 0, sizeof(command_arg));
            sprintf(command_arg, "cd ../../../app/scripts && sh mpls_config -d %s %s %s", if_name, nw, label_out);
            printf("%s\n", command_arg);

            pp = popen(command_arg, "r");
            printProcessInfo(pp);
            pclose(pp);
            break;
        case 'e':
        case 'E':
            nw = strtok(NULL, "_");
            label_out = strtok(NULL, "_");
            label_out_local = strtok(NULL, "_");   
    
            /*
            Enable ifaces
            */

            sprintf(command_arg, "cd ../../../app/scripts && sh mpls_config -c %s", if_name);
            printf("%s\n", command_arg);

            pp = popen(command_arg, "r");
            printProcessInfo(pp);
            pclose(pp);

            /*
            Add MLPLS to network
            */
            memset(command_arg, 0, sizeof(command_arg));
            sprintf(command_arg, "cd ../../../app/scripts && sh mpls_config -a %s %s %s", if_name, nw, label_out);
            printf("%s\n", command_arg);

            pp = popen(command_arg, "r");
            printProcessInfo(pp);
            pclose(pp);

            /*
            Add MLPLS to loopback iface
            */
            memset(command_arg, 0, sizeof(command_arg));
            sprintf(command_arg, "cd ../../../app/scripts && sh mpls_config -l %s", label_out_local);
            printf("%s\n", command_arg);

            pp = popen(command_arg, "r");
            printProcessInfo(pp);
            pclose(pp);
            break;
        case 'f':
        case 'F':
            nw = strtok(NULL, "_");
            label_out = strtok(NULL, "_");
            /*
            Enable ifaces
            */

            sprintf(command_arg, "cd ../../../app/scripts && sh mpls_config -c %s", if_name);
            printf("%s\n", command_arg);

            pp = popen(command_arg, "r");
            printProcessInfo(pp);
            pclose(pp);

            /*
            Add MLPLS to network
            */
            memset(command_arg, 0, sizeof(command_arg));
            sprintf(command_arg, "cd ../../../app/scripts && sh mpls_config -a %s %s %s", if_name, nw, label_out);
            printf("%s\n", command_arg);

            pp = popen(command_arg, "r");
            printProcessInfo(pp);
            pclose(pp);
            break;

        case 'l':
        case 'L':
            break;
            char *label_out_local = strtok(NULL, "_");
            /*
            Add MLPLS to loopback iface
            */
            memset(command_arg, 0, sizeof(command_arg));
            sprintf(command_arg, "cd ../../../app/scripts && sh mpls_config -l %s", label_out_local);
            printf("%s\n", command_arg);

            pp = popen(command_arg, "r");
            printProcessInfo(pp);
            pclose(pp);

        case 's':
        case 'S':
            label_in = strtok(NULL, "_");
            label_out = strtok(NULL, "_");
            ip_out = strtok(NULL, "_");
            /*
            Add MLPLS to loopback iface
            */
            memset(command_arg, 0, sizeof(command_arg));
            sprintf(command_arg, "cd ../../../app/scripts && sh mpls_config -s %s %s %s", label_in, label_out, ip_out);
            printf("%s\n", command_arg);

            pp = popen(command_arg, "r");
            printProcessInfo(pp);
            pclose(pp);
            break;
        default:
            sprintf(result, "MPLS configuration of %s went wrong", if_name); 
            break;
    }
    
    if(option != 'a' || option != 'A')
        sprintf(result, "MPLS configuration of %s is OK", if_name);
}

void execAddMPLSRoute(char* configs, char *result){
    char *machine_name = strtok(configs, "_");
    printf("Add MPLS route to %s\n", machine_name);

    char *nw = strtok(NULL, "_");
    char *label_out = strtok(NULL, "_");
    char *if_name = strtok(NULL, "_");
    FILE *pp;
    char command_arg[1024] = {0};

    /*
    Add MLPLS to network
    */
    memset(command_arg, 0, sizeof(command_arg));
    sprintf(command_arg, "cd ../../../app/scripts && sh mpls_config -d %s %s %s", if_name, nw, label_out);
    printf("%s\n", command_arg);

    pp = popen(command_arg, "r");
    printProcessInfo(pp);
    pclose(pp);

    sprintf(result, "MPLS added route to %s: OK", machine_name);

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
    char *if_name2 = strtok(NULL, "_");

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
    char in_command[MAXLINE] = {0};
    char out_command[MAXLINE] = {0};
    char *route_method = {0};
    char msg[MAXLINE] = {0};
    char res[MAXLINE] = {0};
    char res1[MAXLINE] = {0};
    char route_impl_res[MAXLINE] = {0};

    command_remote = strtok_r(command_local, " ", &command_local);
    printf("\nCommnad Remote: %s\n", command_remote);
    sprintf(out_command, "%s", command_remote);
    
    command_local = strtok(command_local, " ");
    route_method = strtok(NULL, " ");
    sprintf(in_command, "%s", command_local);
    printf("\nCommnad Local: %s\n", in_command);
    printf("Route Method: %s\n", out_command);
    
    /*Set Tunnel Between UAVs*/
    sprintf(msg, "-T_%s", command_remote);
    char* tun_name = strtok(command_remote, "_");
    char* remote_ip = strtok(NULL, "_");
    
    initUAVClient(remote_ip, msg, res);

    char compare_string[MAXLINE] = {0};
    sprintf(compare_string, "Configuration of %s is OK", tun_name);

    int condition = strcmp(res, compare_string);
    if(condition == STR_EQUAL)
        execConfigTun(command_local, res1);

    int condition2 = strcmp(res, res1);
    if(condition2 == STR_EQUAL)
        sprintf(result, "%s configuration applied", tun_name);
    /* Tunnel configuration finish */
    /* Set Routes */
    int route_type;
    if (strcmp(route_method, "IP") == STR_EQUAL)
        route_type = 1;
    if (strcmp(route_method, "MPLS") == STR_EQUAL)
        route_type = 2;

    switch(route_type){
        case 1:
            setIPRoute(tun_name, route_impl_res);
            break;
        case 2:
            printf("MPLS\n");
            mpls_thread_create(remote_ip, in_command, out_command);
            setMPLSRoute(tun_name, route_impl_res);
            break;
        default:
            break;
    }
}

void mpls_thread_create(char *remote_ip, char *in_commands, char *out_commands){
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    targs *args = (targs *)malloc(sizeof(targs));
    targs *args2= (targs *)malloc(sizeof(targs));
    printf("command_local: %s\ncommand_remote:  %s\n", in_commands, out_commands);
    for(t=0; t<NUM_THREADS; t++){
        printf("In main: creating thread %ld\n", t);
        if(t == 0){
            printf("enter thread0\n");
            args->remote_ip=remote_ip;
            args->configs=out_commands;
            args->option=t;
            rc = pthread_create(&threads[t], NULL, mpls_thread_func, (void *)args);
        }
        else
        {
            args2->remote_ip=remote_ip;
            args2->configs=in_commands;
            args2->option=t;
            rc = pthread_create(&threads[t], NULL, mpls_thread_func, (void *)args2);
        }
        pthread_join(threads[t], NULL);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
        }
    }
    //pthread_exit(NULL);
}

void *mpls_thread_func(void *input){


    
    targs* data = (targs*) input;
    char *config_command = ((targs *)data)->configs;
    char *ip_remote = ((targs *)data)->remote_ip;
    int option = ((targs *)data)->option;
    free(data);

    printf("enter thread: %d func\n", option);
    printf("remote_ip: %s\nconfigs: %s\noption: %d\n", ip_remote, config_command, option);
    char *if_name = strtok(config_command, "_");
    printf("Start configuration of %s\n", if_name);
    char *tun_ip_in = strtok(NULL, "_");
    char *tun_ip_out = strtok(NULL, "_");
    char *ip_address = strtok(NULL, "_");
    char *nw = strtok(NULL, "_");
    char *tag = strtok(NULL, "_");
    printf("A_%s_%s_%s\n", if_name, nw, tag);
    char command_to_send[MAXLINE] = {0};
    char result[MAXLINE] = {0};

    switch (option)
    {
        case 0:
            sprintf(command_to_send, "-M'F_%s_%s_%s", if_name, nw, tag);
            initUAVClient(ip_remote, command_to_send, result);
            break;
        case 1:
            sprintf(command_to_send, "F_%s_%s_%s", if_name, nw, tag);
            execConfigMPLS(command_to_send, result);
            break;
        
        default:
            break;
    }
    return NULL;
}


void getLinkDownIface(char* iface_name, char *result){
    int tun_in = (int)iface_name[3] - '0';
    int tun_out = (int)iface_name[5] - '0';
    int dif = tun_out - tun_in;
    for (int i=0; i < sizeof(iface_name); i++){
        result[i] = iface_name[i];
        if(i != 3)
            result[i] = iface_name[i];
        else if(i == 3 && (dif > 1 || dif == 1) && tun_in == 1) 
        {
            result[i] = iface_name[i+2];
            break;
        }
        
        else if(i == 3 && dif == 1 && tun_in > 1)
        {
            int n_ant = (int)iface_name[i] - '0' - 1;
            result[i] = n_ant + '0';
        }
    }
    
}

void setLinkDown(char* configs, char *result){
    printf("enter setLinkDown function\n");
    char *if_name = strtok(configs, "_");

    printf("Set Link Down: %s\n", if_name);
    FILE *pp;
    char command_arg[1024] = {0};
    sprintf(command_arg, "cd ../../../app/scripts && sh tunnel_config -o %s", if_name);
    //printf("%s\n", command_arg);
    pp = popen(command_arg, "r");
    printProcessInfo(pp);
    pclose(pp);
    sprintf(result, "Set Link Down of %s: OK", if_name);
}

void setRouteDown(char* configs, char *result){
    printf("enter setLinkDown function\n");
    char *if_name = strtok(configs, "_");

    printf("Set Link Down: %s\n", if_name);
    FILE *pp;
    char command_arg[1024] = {0};
    sprintf(command_arg, "cd ../../../app/scripts && sh route_config -d %s", if_name);
    //printf("%s\n", command_arg);
    pp = popen(command_arg, "r");
    printProcessInfo(pp);
    pclose(pp);
    sprintf(result, "Set Route Down of %s: OK", if_name);
}

void setIPRoute(char *tun_name, char *result){
    char base_ip[MAXLINE] = {0};
    char node_ip[MAXLINE] = {0};

    /* commands to send*/
    char args[MAXLINE] = {0};
    char command_args[MAXLINE] = {0};
    char command[MAXLINE] = {0};
    char result_config[MAXLINE] = {0};
    char tun_down[MAXLINE] = {0};
    char result_tun_down[MAXLINE] = {0};

    /* set routes */
    int first_element  = (int) tun_name[strlen(tun_name)-3] - '0';
    int last_element   = (int) tun_name[strlen(tun_name)-1] - '0';
    int n = last_element;
    
    int dif = last_element - first_element;

    sprintf(base_ip, "10.0.%d0.1", n);
    for(int i = 0; i < n; i++)
    {        
        if(i == 0)
         {
            /* First network node */
            memset(args, 0, sizeof(args));
            memset(command, 0, sizeof(command));
            memset(command_args, 0, sizeof(command_args));
            memset(result_config, 0, sizeof(result_config));
            printf("Base ID: %d\n", i);
            sprintf(args, "%d_%s", i, tun_name);
            get_command_args("get_command", 2, args, command_args);
            sprintf(command, "-R_%s", command_args);
            printf("command: %s base ip: %s\n", command, base_ip);
            initUAVClient(base_ip, command, result_config);
        }  
        else if(i == n-1)
        {
            
            /* Intermedious nodes */
            
            memset(args, 0, sizeof(args));
            memset(command, 0, sizeof(command));
            memset(command_args, 0, sizeof(command_args));
            memset(result_config, 0, sizeof(result_config));
            memset(result_config, 0, sizeof(result_config));
            memset(node_ip, 0, sizeof(node_ip));
            if(dif > 1)
            {
                printf("UAV%d ID: %d\n", n-dif, n-dif);
                sprintf(node_ip, "10.0.%d%d.1", n-dif, n);
                
            }
            else
            {
                printf("UAV%d ID: %d\n", i, i);
                sprintf(node_ip, "10.0.%d%d.1", n-1, n);
            }
            sprintf(args, "%d_%s_%s", i, tun_name, "tables");
            get_command_args("get_command", 3, args, command_args);
            sprintf(command, "-P_%s", command_args);
            printf("command: %s node ip:%s\n", command, node_ip);
            initUAVClient(node_ip, command, result_config);
        }
    }
    /* Last network node */
    memset(args, 0, sizeof(args));
    memset(command, 0, sizeof(command));
    memset(command_args, 0, sizeof(command_args));
    memset(result_config, 0, sizeof(result_config));
    printf("UAV%d ID: %d\n", n, n);
    sprintf(args, "%d_%s", n, tun_name);
    get_command_args("get_command", 2, args, command_args);
    memset(result_tun_down, 0, sizeof(result_tun_down));
    
    if(dif == 1)
    {
        memset(tun_down, 0, sizeof(tun_down));
        getLinkDownIface(tun_name, tun_down);
        setLinkDown(tun_down,  result_tun_down);
    }
    execConfigRoute(command_args, result_config);

}

void setMPLSRoute(char *tun_name, char *result){
    char base_ip[MAXLINE] = {0};
    char node_ip[MAXLINE] = {0};

    /* commands to send*/
    char args[MAXLINE] = {0};
    char command_args[MAXLINE] = {0};
    char command[MAXLINE] = {0};
    char result_config[MAXLINE] = {0};

    /* set routes */
    int first_element  = (int) tun_name[strlen(tun_name)-3] - '0';
    int last_element   = (int) tun_name[strlen(tun_name)-1] - '0';
    int n = last_element;
    int dif = last_element - first_element;
    int check_base_result = 0;
    char *token, *add_route_args;
    char *add_base_route_token = {0};
    char *add_uav_route_token = {0};
    char tun_down[MAXLINE] = {0};
    char result_tun_down[MAXLINE] = {0};
    if(first_element > 1 && last_element >= 3)
        sprintf(base_ip, "10.0.10.1");
    else
        sprintf(base_ip, "10.0.%d0.1", n);
    printf("MPLS Route config\n");
    for(int i = 0; i < n; i++)
    {        
        if(i == 0)
        {
            /* Base Network Node */
            printf("\tBase Configurations\n");
            memset(args, 0, sizeof(args));
            memset(command, 0, sizeof(command));
            memset(command_args, 0, sizeof(command_args));
            memset(result_config, 0, sizeof(result_config));
            sprintf(args, "%d_%s", i, tun_name);
            get_mpls_command_args("get_mpls_command", 2, args, command_args);
            sprintf(command, "-N_Base_%s", command_args);
            printf("\tcommand_to_send: %s\n", command);
            initUAVClient(base_ip, command, result_config);
            
            // printf("Response from Base: %s\n", result_config);
            if(first_element < 2)
            {
                memset(command, 0, sizeof(command));
                memset(result_tun_down, 0, sizeof(result_tun_down));
                memset(tun_down, 0, sizeof(tun_down));
                getLinkDownIface(tun_name, tun_down);                
                sprintf(command, "-D_%s", tun_down);
                printf("\tcommand_to_send: %s\n", command);
                initUavMplsClient(base_ip, command, result_config);
            }

            if(strcmp(result_config, "MPLS added route to Base: OK") == STR_EQUAL)
                check_base_result = 1;  
        }
        else if(i== n-2 && n-2 > 0){
            /* UAV1 Network Node */
            printf("\n\tUAV1 Configurations\n");
            memset(node_ip, 0, sizeof(node_ip));
            printf("\tUAV%d ID: %d\n", i, i);
            sprintf(node_ip, "10.0.%d%d.1", n-2, n);
            printf("\tUAV%d IP: %s\n", i, node_ip);
            sprintf(args, "%d_%s", i, tun_name);
            memset(args, 0, sizeof(args));
            memset(command, 0, sizeof(command));
            memset(command_args, 0, sizeof(command_args));
            memset(result_config, 0, sizeof(result_config));
            
            sprintf(args, "%d_%s", i, tun_name);
            printf("\t\tArgs: %s\n", args);
            get_mpls_command_args("get_mpls_command", 2, args, command_args);
            
            token = strtok(command_args, "|");
            add_uav_route_token = token;
            
            token = strtok(NULL, "|");
            sprintf(command, "-M'S_%s", token);
            printf("\t\tCommand: %s\n", command);
            initUAVClient(node_ip, command, result_config);
            sprintf(command, "-M'A_%s", add_uav_route_token);
            printf("\t\tRoute Add Command: %s\n", command);
            memset(result_config, 0, sizeof(result_config));
            initUAVClient(node_ip, command, result_config);
            //Delete prior configuration 
            memset(command, 0, sizeof(command));
            memset(result_tun_down, 0, sizeof(result_tun_down));
            memset(tun_down, 0, sizeof(tun_down));
            getLinkDownIface(tun_name, tun_down);                
            sprintf(command, "-O_%s", tun_down);
            printf("\tcommand_to_send: %s\n", command);
            initUavMplsClient(node_ip, command, result_config);
        }

        else if(i == n-1)
        {
            
            /* Intermedious nodes */
            printf("\tUAV%d ID: %d\n", i, i);
            memset(args, 0, sizeof(args));
            memset(command, 0, sizeof(command));
            memset(command_args, 0, sizeof(command_args));
            memset(result_config, 0, sizeof(result_config));
            
            memset(node_ip, 0, sizeof(node_ip));
            if(dif > 1)
            {
                printf("UAV%d ID: %d\n", n-dif, n-dif);
                sprintf(node_ip, "10.0.%d%d.1", n-dif, n);
                sprintf(args, "%d_%s", n-dif, tun_name);
                printf("args: %s\n", args);
                
            }
            else
            {
                printf("UAV%d ID: %d\n", i, i);
                sprintf(node_ip, "10.0.%d%d.1", n-1, n);
                sprintf(args, "%d_%s", i, tun_name);
            }
            
            get_mpls_command_args("get_mpls_command", 2, args, command_args);

            token = strtok(command_args, "|");
            while(token != NULL){
                sprintf(command, "-M'S_%s", token);
                initUAVClient(node_ip, command, result_config);
                token = strtok(NULL, "|");
                memset(result_config, 0, sizeof(result_config));
                memset(command, 0, sizeof(command));
            }
            // sprintf(command, "-M'S_%s", token);
            // initUAVClient(node_ip, command, result_config);

            // memset(result_config, 0, sizeof(result_config));
            // memset(command, 0, sizeof(command));
            // token = strtok(NULL, "|");
            // sprintf(command, "-M'S_%s", token);
            // initUAVClient(node_ip, command, result_config);
   
        }
    }
    
    /* Last network node */
    memset(args, 0, sizeof(args));
    memset(command_args, 0, sizeof(command_args));
    memset(result_config, 0, sizeof(result_config));
    memset(command, 0, sizeof(command));
    printf("UAV%d ID: %d\n", n, n);

    sprintf(args, "%d_%s_%s", n, tun_name, "lastNode");
    get_mpls_command_args("get_mpls_command", 3 ,args, command_args);
    token = strtok(command_args, "|");
    // if(first_element > 1){
        while(token != NULL){
            sprintf(command, "D_%s", command_args);
            execConfigMPLS(command, result_config);
            token = strtok(NULL, "|");
            memset(result_config, 0, sizeof(result_config));
            memset(command, 0, sizeof(command));
        }
    // }
    // else
    // {
    //         memset(result_config, 0, sizeof(result_config));
    //         memset(command, 0, sizeof(command));
    //         sprintf(command, "-M'S_%s", token);
    //         execConfigMPLS(command, result_config);
    // }
    
    
    if(dif == 1)
    {
        memset(result_tun_down, 0, sizeof(result_tun_down));
        memset(tun_down, 0, sizeof(tun_down));
        getLinkDownIface(tun_name, tun_down);
        printf("%s\n", tun_down);
        setRouteDown(tun_down,  result_tun_down);
    }

}


/*
    Auxiliar functions
*/

void printProcessInfo(FILE *pp){
    if (pp != NULL) {
        while (1) {
            char *line;
            char buf[1000];
            line = fgets(buf, sizeof buf, pp);
            if (line == NULL) break;
            printf("%s", line); /* line includes '\n' */
        }
    }
}

void get_command_args(char *function_name, int n_args, char *args, char *result){
    PyObject *strret, *pModule, *pFunc, *pArgs;
    printf("get_command_args:\n\
        \tfunction_name: %s\n\
        \tn_args: %d\n\
        \targs: %s\n", function_name, n_args, args);
    
    Py_Initialize();
    int arg1;
    char *token;
    char *arg2;
    char *arg3;
    PyObject *sys_path = PySys_GetObject("path");
    PyList_Append(sys_path, PyUnicode_FromString("../source"));
    PyObject* fname = PyUnicode_FromString("get_command");
    pModule = PyImport_Import(fname);
    if (pModule == NULL) {
        PyErr_Print();
        exit(-1);
    }

    pFunc = PyObject_GetAttrString(pModule, function_name);
    if (pFunc == NULL) {
        PyErr_Print();
        exit(-1);
    }

    switch (n_args)
    {
        case 2:
            token = strtok(args, "_");
            arg1 = atoi(token);
            arg2 = strtok(NULL ,"_");
            pArgs = Py_BuildValue("(is)", arg1, arg2);
            break;
        case 3:
            token = strtok(args, "_");
            arg1 = atoi(token);
            arg2 = strtok(NULL ,"_");
            arg3 = strtok(NULL ,"_");
            pArgs = Py_BuildValue("(iss)", arg1, arg2, arg3);
            /* code */
            break;
        default:
            printf("invalid number of args");
            pArgs = Py_BuildValue("(is)", "None", "None");
            break;
    }
    
    strret = PyEval_CallObject(pFunc, pArgs);

    sprintf(result, "%s", _PyUnicode_AsString(strret));
    
    printf("Returned string: %s\n", result);
    Py_Finalize();
}

void get_mpls_command_args(char *function_name, int n_args, char *args, char *result){
     printf("get_mpls_command_args:\n\
        \tfunction_name: %s\n\
        \targs: %s\n", function_name, /* n_args, */ args);

    PyObject *strret, *pModule, *pFunc, *pArgs;

    char *token;
    int arg1;
    char *arg2, *arg3;

    Py_Initialize();
    PyObject *sys_path = PySys_GetObject("path");
    
    PyList_Append(sys_path, PyUnicode_FromString("../source"));
    PyObject* fname = PyUnicode_FromString("get_command");
    pModule = PyImport_Import(fname);
    if (pModule == NULL) {
         PyErr_Print();
         exit(-1);
    }
    
    pFunc = PyObject_GetAttrString(pModule, function_name);
    if (pFunc == NULL) {
        PyErr_Print();
        exit(-1);
     }
    switch (n_args)
    {
        case 2:
            token = strtok(args, "_");
            arg1 = atoi(token);
            arg2 = strtok(NULL ,"_");
            pArgs = Py_BuildValue("(is)", arg1, arg2);
            break;
        case 3:
            token = strtok(args, "_");
            arg1 = atoi(token);
            arg2 = strtok(NULL ,"_");
            arg3 = strtok(NULL ,"_");
            pArgs = Py_BuildValue("(iss)", arg1, arg2, arg3);
            break;
        
        default:
            break;
    }
    strret = PyEval_CallObject(pFunc, pArgs);
    sprintf(result, "%s", _PyUnicode_AsString(strret));
    printf("Returned string: %s\n", result);
    Py_Finalize();
}
