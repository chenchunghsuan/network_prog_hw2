#include <stdio.h>
#include <string.h>   
#include <stdlib.h>    
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread


//the thread function
void *connection_handler(void *);
char temp[2000],client2[20],connfd[10];
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , *new_sock,i;
    struct sockaddr_in server , client;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8080 );
if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
    
    //Listen
    listen(socket_desc , 10);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    //c = sizeof(struct sockaddr_in);
for(i=0;i<10;i++) client2[i]=-1;
   
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;
if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
        puts("Handler assigned");
    }

    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }

    return 0;
}
int m=0;
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size,i;
    char *message , client_message[2000];
printf("Connected successfully client:%d\n", sock);
    //Receive a message from client
    client2[m]=sock;
m++;
   while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
	for(i=0;i<10;i++){
if(client2[i]!=-1)
        write(client2[i] , client_message , strlen(client_message));
	}
        printf("The message from client is\n%s\n",client_message);
    }
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
    //Free the socket pointer
    free(socket_desc);
    close(sock);
    pthread_exit(NULL); 
    return 0;
}

