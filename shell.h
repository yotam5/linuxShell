#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h> /* for malloc() */
#include <string.h> /* for strcpy() */
#include <unistd.h>
#include <sys/wait.h>

#define true 1
#define FORK_ERROR -1
#define PBUFF_SIZE 128
#define MAX_CMD_LENGTH 256

void initCmd(char directory[]);
void type_prompt();
void getCmd(char directory[], char *argv_child[], char *evnp_child[]);
void printCurrState(char directory[], char *argv_child[], char *evnp_child[]);

#endif
