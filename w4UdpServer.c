#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    int n;
    socklen_t len;
    char msg[1024];
    struct sockaddr_in servaddr, cliaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(5035);
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    for (;;)
    {
        len = sizeof(cliaddr);
        n = recvfrom(sockfd, msg, 1024, 0, (struct sockaddr *)&cliaddr, &len);
        printf("\n Client's Message : %s\n", msg);
        sendto(sockfd, msg, n, 0, (struct sockaddr *)&cliaddr, len);
    }
    return 0;
}