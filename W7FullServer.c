#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main()
{
	int ClientSocketDescriptor,SocketDescriptor;
	struct sockaddr_in sa,clientAddress;
	char recvBuffer[80000],sendBuffer[80000];
	socklen_t clientLength;
	pid_t cpid;

	bzero(&sa,sizeof(sa));
	sa.sin_family=AF_INET;
	sa.sin_addr.s_addr=htonl(INADDR_ANY);
	sa.sin_port=htons(9652);
	SocketDescriptor=socket(AF_INET,SOCK_STREAM,0);

	bind(SocketDescriptor,(struct sockaddr*)&sa,sizeof(sa));
	listen(SocketDescriptor,5);
	printf("%s\n","Server is running ...");
	ClientSocketDescriptor=accept(SocketDescriptor,(struct sockaddr*)&clientAddress,&clientLength);
    
	cpid=fork();
	if(cpid==0)
	{
		while(1)
		{
			bzero(&recvBuffer,sizeof(recvBuffer));
			recv(ClientSocketDescriptor,recvBuffer,sizeof(recvBuffer),0);
			printf("\nCLIENT : %s\n",recvBuffer);
		}
	}
	else
	{
		while(1)
		{
			bzero(&sendBuffer,sizeof(sendBuffer));
			printf("\nType a message here ... ");
			fgets(sendBuffer,80000,stdin);
			send(ClientSocketDescriptor,sendBuffer,strlen(sendBuffer)+1,0);
			printf("\nMessage sent !\n");
			/*			
			time_t tick;
		    time(&tick);
			send(ClientSocketDescriptor,ctime(&tick),strlen(ctime(&tick))+1,0);*/
		}
	}
return 0;
}