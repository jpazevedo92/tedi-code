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

/* Constant variables / MACROS */
#define PORT 8080
/* Function Headers */
void initClient(char *iface_name, char *srv_ip, char *clt_message);

void checkHostName(int hostname);
void checkHostEntry(struct hostent * hostentry);
void getHostandIp(char* iface, char *result);

void initServer(char *iface_name);
void getIp(char* iface, char *result);


#endif /* SOC_UTILS_H_*/
