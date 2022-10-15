#include "shell.h"

int main(int argc, char *argv[], char *evnp[])
{
  char *argv_child[] = {NULL, NULL, NULL, NULL};
  char *evnp_child[] = {NULL};
  char directory[MAX_CMD_LENGTH] = {0};
  int argc_child = {0};
  int status = {0};

  while(true)
    {
      initCmd(directory);
      type_prompt();
      getCmd(directory, argv_child, evnp_child);
      argc_child = getArgv(argv_child); /* getArgv() returns the arguments' amount */
      /*printCurrState(&directory, argv_child, evnp_child);*/
      printArgs(argc_child, argv_child);
      int cpid = fork();
      if(cpid == FORK_ERROR)
      {
        exit(1);
      }
      if(cpid)
      {
        printf("waiting\n");
        waitpid(-1, &status, 0);
      }
      else
        {
        printf("argc: %d\n", argc_child);
        printCurrState(directory, argv_child, evnp_child);
         if (execve((const char*)directory, argv_child, evnp_child) == EXECVE_FAILED)
              printf("%s: command not found\n", argv_child[0]);
        }
      freeArgs(argc_child, argv_child);
  }
  return 0;
}

void type_prompt()
{
  /*finds the user's name*/
  char *loginBuff;
  loginBuff = (char*)malloc(MAX_USERNAME_LENGTH*sizeof(char));
  cuserid(loginBuff);

  /*finds the current working directory*/
  char pbuff[PBUFF_SIZE] = {0};
  size_t size = {PBUFF_SIZE};
  getcwd(pbuff, size);
  
  /*prints colorful prompt*/
  printf("\e[1;32m\n%s@@\e[0m:", loginBuff);
  printf ("\e[1;34m%s\e[0m$ ", pbuff);

  free(loginBuff); 
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

int getArgv(char *argv_child[])
{
  int argc_child = {1};
  char *line = {0};
  size_t len = 0;
  ssize_t lineSize = 0;

  /*perror("befor if");*/
  if(getline(&line, &len, stdin))
  {
    /*printf("line: %s\n", line);*/
    if(isEmpty(line))
      return 0;
   /* perror("inside if");
    printf("line: <%s>\n", line);*/
    char *token = NULL;
    /*perror("before strtok");*/
    token = strtok(line, " ");
    /*perror("after strtok");*/
    /*printf("first token: <%s>\n", token);*/
    while(token)
      {
        if(isEmpty(token)) 
          break;
        if(lastCharIsEnter(token))
        {
          token = removeEnter(token);
          argv_child[argc_child] = (char*)malloc(strlen(token));
          strncpy(argv_child[argc_child], token, strlen(token));
          return argc_child;
        }
        argv_child[argc_child] = (char*)malloc(strlen(token));
        strcpy(argv_child[argc_child], token);
        /*printf("token: %s\n", token);
        printf("argv[%d]: %s\n", argc_child, argv_child[argc_child]);*/
        ++argc_child;
        token = strtok(NULL, " ");
      }
    /*scanf("%s", arg);
    argv_child[i] = (char*)malloc(strlen(arg));
    strcpy(argv_child[i], arg);*/
  }
  /*perror("after if");*/
  return argc_child - 1;
}

void freeArgs(int argc, char *argv[])
{
  int i = {0};
  for(i; i <= argc; ++i)
    {
      free(argv[i]);
    }
}

/*DEBUGGING TOOLS*/

void printCurrState(char directory[], char *argv_child[], char *evnp_child[])
{
  printf("\e[1;31mcurr state:\e[0m \ndir: %s \nargv: %s \nevnp: %s\n", directory, argv_child[0], evnp_child[0]);
}

void printArgs(int argc, char *argv[])
{
  printf("\e[1;31marguments:\e[0m\n");
  int i = {0};
  for(i; i <= argc; ++i)
    {
      printf("The %d argument is: %s\n", i, argv[i]);
    }
}

/*UTILITIES*/

int isEmpty(char *line)
{
  char currChar;
  currChar = *line;
  while(currChar != '\n')
    {
      if(!isspace(currChar))
        return false;
      ++currChar;
    }
  return true;
}

int lastCharIsEnter(char *line)
{
  return(line[strlen(line) - 1] == '\n');
}

char* removeEnter(char *line)
{
  /*char *token = NULL;
  token = strtok(line, )
  printf("")*/
  return(strtok(line, "\n"));
}
