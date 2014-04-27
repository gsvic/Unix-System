/*
A simple TCP Server Socket that executes Unix bash commands

Developed by :
Giannakouris -  Salalidis Victor , victorasgs@gmail.com
*/

#include "apue.h"
#include "error.c"
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define true 1
#define false 0
#define MAX_REQUEST_LENGTH 256



int main(int argc, char *argv[]){

    int fd;
    struct sockaddr_in address;

    memset(&address,'0',sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(5000);

    fd = socket(AF_INET,SOCK_STREAM,0);

    /*Binding*/
    if ( bind(fd,(struct sockaddr *)&address,sizeof(address)) < 0 )
        err_sys("bind error");

    /*Listening*/
    if ( listen(fd,10) < 0 )
        err_sys("listen error");

    while ( true ){

        char buff[MAX_REQUEST_LENGTH];
        int request_fd = accept(fd, (struct sockaddr *)NULL,NULL);

        int r;

        if ( ( r = read(request_fd,buff,sizeof(buff)-1) ) < 0 )
            err_sys("read error");


        //System Call
        system(buff);

        //Cleaning The Buffer
        memset(buff,0,sizeof(buff));
        close(request_fd);
    }

}


