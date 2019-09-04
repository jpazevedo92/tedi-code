#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COLUMNS 2

void get_commands_array(char *str_rcvd, char *cmd_array[][COLUMNS]);
int get_n_uavs(char *str_rcvd);

#endif
