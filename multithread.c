#include<stdio.h>
#include<string.h>
#include<sys/type.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#define port 8080
#define client_num 10
#define s 80 
void *connect_handler(void *thread_id){
int num=(int)thread_id;
int sock;
struct sockaddr_in server_addr;
char buf[s],buff[s];
if((sock=socket(AF_INET,SOCK_STREAM,0))<0) perror("Socket");
bzero((char *) &server_addr,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
server_addr.sin_port=htons(port);
if(connect(sock,(struct sockaddr *) &server_addr,sizeof(server_addr))<0) perror("select");
printf("COnnection Success-----\n");
while(1){
printf("THREAD %d\n",num);

}
}
int main()
{
int socket_des,new_socket,i;
pthread_t new_thread;
for(i=0;i<client_num;i++)
{
if(pthread_create(&new_thread,NULL,))
}
return 0;
}
