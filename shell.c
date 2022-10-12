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

int main(int argc, char *argv[], char *evnp[])
{
  char *argv_child[] = {NULL, NULL};
  char *evnp_child[] = {NULL};
  char directory[MAX_CMD_LENGTH] = {0};
  int status = {0};

  while(true)
    {
      initCmd(&directory);
      type_prompt();
      getCmd(&directory, argv_child, evnp_child);
      /*printCurrState(&directory, argv_child, evnp_child);*/
      int cpid = fork();
      if(cpid == FORK_ERROR)
      {
        perror("error while fork()\n");
        exit(1);
      }
      if(cpid)
        waitpid(-1, &status, 0);
      else 
        execve((const char*)directory, argv_child, evnp_child);
      free(argv_child[0]);
  }
  return 0;
}

void type_prompt()
{
  char pbuff[PBUFF_SIZE] = {0};
  size_t size = {PBUFF_SIZE};
  getcwd(pbuff, size);
  printf("\e[1;32m\nuser@@\e[0m:");
  printf ("\e[1;34m%s\e[0m$ ", pbuff);
}

void initCmd(char directory[])
{
  strcpy(directory, "/bin/");
}

void getCmd(char directory[], char *argv_child[], char *evnp_child[])
{
  char cmd[MAX_CMD_LENGTH] = {0};
  scanf("%s", cmd);
  /*cmd = strtok(cmd,' ','\t','\n');*/
  argv_child[0] = (char*)malloc(strlen(cmd));
  strcpy(argv_child[0], cmd);
  strcat(directory, cmd);
}



void printCurrState(char directory[], char *argv_child[], char *evnp_child[])
{
  printf("\e[1;31mcurr state:\e[0m \ndir: %s \nargv: %s \nevnp: %s\n", directory, argv_child[0], evnp_child[0]);
}
