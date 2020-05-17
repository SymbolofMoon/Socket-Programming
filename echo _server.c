#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define ERROR -1
#define MAX_CLIENTS 2
#define MAX_DATA 1024


void main(int argc , char **argv ){

    int sock ;
    int new;

    struct sockaddr_in server, client;
    int sockaddr_len = sizeof(struct sockaddr_in);
    int data_len;

    char data[MAX_DATA];
    int sent;

    if ((sock=socket(AF_INET,SOCK_STREAM,0))== ERROR)
    {

        perror("Socket: ");
        exit(-1);
        /* code */
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(10000);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero, 8);

    

    if ((bind(sock, (struct sockaddr *)&server,sockaddr_len))==ERROR)
    {
        /* code */perror("bind");
        exit(-1);
    }

    if ((listen(sock, MAX_CLIENTS))==ERROR){
        perror("listen");
        exit(-1);
    }
    
    while(1){
      if ((new= accept(sock,(struct sockaddr *)&client,&sockaddr_len) )==ERROR)

        perror("accept");
        exit(-1);
      }

      printf("New Client connected from port no %d and IP %s\n",ntohs(client.sin_port),inet_ntoa(client.sin_addr));

     data_len = 1;
     while (data_len)
     {
         data_len = recv(new,data,MAX_DATA,0);
         if(data_len){
             send(new,data,data_len,0);
             data[data_len]='\0';
             printf("Sent msg: %s",data);

         }
     }
     
     printf("Sent %d bytes to client : %s\n",sent,inet_ntoa(client.sin_addr));

     close(new);
      
    }
