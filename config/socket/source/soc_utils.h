#ifndef SOC_UTILS_H_
#define SOC_UTILS_H_
/* Includes section */
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
#include <ifaddrs.h>
#include <pthread.h>
#include <python3.6/Python.h>

/* Constant variables / MACROS */
#define PORT        8000
#define PORT1       8001
#define MAXLINE     1024
#define STR_EQUAL   0 
#define False       0
#define True        1

#define IP          1   
#define ADDRESS     2
#define MASK        3

#define NUM_THREADS     2

struct thread_args
 {
     char *remote_ip; 
     char *configs; 
     int option;
} typedef targs;

/* Function Headers */

void initClient(char *srv_ip, char *clt_message);
void initUAVClient(char *srv_ip, char *clt_message, char *result);
//void initClient(char *iface_name, char *srv_ip, char *clt_message);

void checkHostName(int hostname);
void checkHostEntry(struct hostent * hostentry);
void getIfIp(char* iface, char *result);
void getMaskPrefixLength(char *mask, char *result);
void print_ip(unsigned int ip, char *result);

void initServer();
//void initServer(char *iface_name);
//void getIp(char* iface, char *result);
void execCommand(char* command, char *result);
void execConfigTun(char* configs, char *result);
void printProcessInfo(FILE *pp);
void execAliveCheck(char *result);
void execInitFirmware(char* configs, char *result);
void execUavTun(char* configs, char *result);
void execConfigRoute(char* configs, char *result);
void execConfigIpTables(char* configs, char *result);
void execConfigMPLS(char* configs, char *result);
void mpls_thread_create(char *remote_ip, char *in_commands, char *out_commands);
void *mpls_thread_func(void *input);
void initUavMplsClient(char *srv_ip, char *clt_message, char *result);
void execAddMPLSRoute(char* configs, char *result);
void setUAVTunnel(char* configs, char *result);
void getCommand(char* iface, char *result, int option);
void setLinkDown(char* configs, char *result);
void setRouteDown(char* configs, char *result);
void getLinkDownIface(char* iface_name, char *result);
void get_command_args(char *function_name, int n_args, char *args, char * result);
void get_mpls_command_args(char *function_name, int n_args, char *args, char * result);
void setIPRoute(char *tun_name, char *result);
void setMPLSRoute(char *tun_name, char *result);


#endif /* SOC_UTILS_H_*/
