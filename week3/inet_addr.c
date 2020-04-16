#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	char *addr1="127.212.124.78";
	char *addr2="127.212.124.256";	//255�� max�ε� 256 �Ѿ -> invalid ip address 

	unsigned long conv_addr=inet_addr(addr1);	//conversion of the address by using inet_addr
	if(conv_addr==INADDR_NONE)
		printf("Error occured! \n");
	else
		printf("Network ordered integer addr: %#lx \n", conv_addr); //0x4e7cd47f���
	
	conv_addr=inet_addr(addr2);
	if(conv_addr==INADDR_NONE)
		printf("Error occureded \n");
	else
		printf("Network ordered integer addr: %#lx \n\n", conv_addr);//����
	return 0;
}