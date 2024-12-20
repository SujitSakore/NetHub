//Write a socket program in C to transfer a file from the client to server in UDP. 

#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#define MAX 200
#define PORT 43454
#define SA struct sockaddr
void func(int sockfd)
{
char buff[MAX];
FILE *fp;
int n;
bzero(buff,sizeof(buff));
fp=fopen("clifile","r");
bzero(buff,MAX);
n=0;
while((buff[n++]=getc(fp))!=EOF);
write(sockfd,buff,sizeof(buff));
close(fp);
}
int main()
{
int sockfd,connfd;
struct sockaddr_in servaddr,cli;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd==-1)
{
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(PORT);
if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr))!=0)
{
printf("connection with the server failed...\n");
exit(0);
}
else
printf("connected to the server..\n");
func(sockfd);
close(sockfd);
}

