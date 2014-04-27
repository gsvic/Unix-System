#include "apue.h"
#include "error.c"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define MAX_SIZE 256

char *command(int,char *[]);

int main(int argc, char *argv[]){

    struct sockaddr_in server;
    int fd;
    char buffer[MAX_SIZE];

    memset(&server,'0',sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ( (fd = socket(AF_INET,SOCK_STREAM,0)) < 0 )
        err_sys("socket error");

    if(connect(fd, (struct sockaddr *)&server, sizeof(server))<0)
        err_sys("connect error");

    char *cmd = command(argc,argv);

    write(fd,cmd,strlen(cmd));

    printf("Success, cmd : %s\n",cmd);
}

char *command(int argc,char *argv[]){
    char *cmd = NULL;

    if ( argc == 1 ){
        err_sys("You must specify some arguments");
    }
    else{
        cmd = malloc(sizeof(char)*strlen(argv[1]));
        if (cmd==NULL) puts("NULL");
        strcpy(cmd,argv[1]);
        int i;
        for ( i = 2; i < argc; ++i){
            realloc(cmd, strlen(argv[i]));
            strcat(cmd," ");
            strcat(cmd,argv[i]);
        }
        return cmd;
    }

    }



