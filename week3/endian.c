#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	unsigned short host_port = 0x1234;
	unsigned short net_port;
	unsigned long host_address = 0x1234;
	unsigned long net_address;


	net_port = htons(host_port);
	net_address = htonl(host_address);

	printf("Host ordered port %#x \n", host_port);
	printf("Network ordered port %#x \n", net_port);
	printf("Host ordered address %#x \n", host_address);
	printf("Network ordered address %#x \n", net_address);
	 
	return 0;
}
