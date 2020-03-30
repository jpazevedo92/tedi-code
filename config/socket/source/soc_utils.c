#include "soc_utils.h"

/*
    Client init function 
*/
void initClient(char *srv_ip, char *clt_message)
{
    printf("Socket Client: \n\tcommand: %s \n\tserver_ip: %s\n", clt_message, srv_ip);
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
    printf("Socket Client: \n\tcommand: %s \n\tserver_ip: %s\n", clt_message, srv_ip);

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

/*
    Protocol Command functions
*/

void execCommand(char* command, char *result){
	
    char *token; 
    token = strtok_r(command, "_", &command);
    char option = token[1];
    switch(option){
        case 'a':
        case 'A':
            execAliveCheck(result);
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
    char msg[MAXLINE] = {0};
    char res[MAXLINE] = {0};
    char res1[MAXLINE] = {0};
    char base_ip[MAXLINE] = {0};
    char node_ip[MAXLINE] = {0};
    /* commands to send*/

    char args[MAXLINE] = {0};
    char command_args[MAXLINE] = {0};
    char command[MAXLINE] = {0};
    char result_config[MAXLINE] = {0};
    
    command_remote = strtok_r(command_local, " ", &command_local);
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
    int n = tun_name[strlen(tun_name)-1] - '0';
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
            printf("command: %s base ip:%s\n", command, base_ip);
            initUAVClient(base_ip, command, result_config);
        }  else if(i == n-1)
        {
            /* Intermedious nodes */
            printf("UAV%d ID: %d\n", i, i);
            memset(args, 0, sizeof(args));
            memset(command, 0, sizeof(command));
            memset(command_args, 0, sizeof(command_args));
            memset(result_config, 0, sizeof(result_config));
            memset(result_config, 0, sizeof(result_config));
            memset(node_ip, 0, sizeof(node_ip));
            sprintf(node_ip, "10.0.%d%d.1", n-1, n);
            sprintf(args, "%d_%s_%s", i, tun_name, "tables");
            get_command_args("get_command", 3, args, command_args);
            sprintf(command, "-P_%s", command_args);
            printf("command: %s base ip:%s\n", command, base_ip);
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
    execConfigRoute(command_args, result_config);
    //initUAVClient(base_ip, command, result_config);

     if(condition2 == STR_EQUAL)
        sprintf(result, "%s configuration applied", tun_name);

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

void get_command_args(char *function_name, int n_args, char *args, char * result){
    printf("get_command_args:\n\
        \tfunction_name: %s\n\
        \tn_args: %d\n\
        \targs: %s\n", function_name, n_args, args);
    PyObject *strret, *pModule, *pFunc, *pArgs;
    Py_Initialize();
    int arg1;
    char *token;
    char *arg2;
    char *arg3;
    PyObject *sys_path = PySys_GetObject("path");
    //~/Repos/tedi-uavcommandforward/1_Code/tests
    PyList_Append(sys_path, PyUnicode_FromString("../source"));
    PyObject* fname = PyUnicode_FromString("get_command");
    //PyObject* module = PyImport_Import(fname);
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