#include <sys/types.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <complex.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <stdlib.h>
int main()
{
    struct sockaddr_in sin = {0};
    struct arpreq myarp = {{0}};
    unsigned char *ptr;
    int sd;
    sin.sin_family = AF_INET;
    printf("Enter IP address: ");
    char ip[20];
    scanf("%s", ip);

    memcpy(&myarp.arp_pa, &sin, sizeof(myarp.arp_pa));
    strcpy(myarp.arp_dev, "echo");
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    ptr = &myarp.arp_pa.sa_data[0];
    printf("\nMAC Address for '%s' : ", ip);
    printf("%p:%p:%p:%p:%p:%p\n", ptr, (ptr + 1), (ptr + 2), (ptr + 3), (ptr + 4), (ptr + 5));
return 0;
}