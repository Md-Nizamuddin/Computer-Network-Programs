#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
	int SocketDescriptor;
	struct sockaddr_in SocketAddress;
	char sendBuffer[80000],recvBuffer[80000];
	pid_t cpid;

	bzero(&SocketAddress,sizeof(SocketAddress));
	SocketAddress.sin_family=AF_INET;
	SocketAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
	SocketAddress.sin_port=htons(9652);
	SocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
	connect(SocketDescriptor,(struct sockaddr*)&SocketAddress,sizeof(SocketAddress));
    
	cpid=fork();
	if(cpid==0)
	{
		while(1)
		{
			bzero(&sendBuffer,sizeof(sendBuffer));
			printf("\nType a message here ... ");
			fgets(sendBuffer,80000,stdin);
			send(SocketDescriptor,sendBuffer,strlen(sendBuffer)+1,0);
			printf("\nMessage sent !\n");
		}
	}
	else
	{
		while(1)
		{
			bzero(&recvBuffer,sizeof(recvBuffer));
			recv(SocketDescriptor,recvBuffer,sizeof(recvBuffer),0);
			printf("\nSERVER : %s\n",recvBuffer);
		}
	}
return 0;
}
