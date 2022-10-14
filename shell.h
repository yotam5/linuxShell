#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h> /* for malloc() */
#include <string.h> /* for strcpy() */
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h> /* for isspace() */ 

#define true 1
#define false 0
#define FORK_ERROR -1
#define EXECVE_FAILED -1
#define PBUFF_SIZE 128
#define MAX_USERNAME_LENGTH 64
#define MAX_CMD_LENGTH 256

void initCmd(char directory[]);
void freeArgs(int argc, char *argv[]);
void type_prompt();
void getCmd(char directory[], char *argv_child[], char *evnp_child[]);
int getArgv(char *argv_child[]);
void printCurrState(char directory[], char *argv_child[], char *evnp_child[]);
void printArgs(int argc, char *argv[]);
int isEmpty(char *line);
int lastCharIsEnter(char *line);
char* removeEnter(char *line);

#endif
