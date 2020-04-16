#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in addr1, addr2;
	char *str_ptr;
	char str_arr[20];
   
	addr1.sin_addr.s_addr=htonl(0x10203040);
	addr2.sin_addr.s_addr=htonl(0x10101010);
	
	str_ptr=inet_ntoa(addr1.sin_addr);	//inet_ntoa : converting back the network orderend decimal number into human reaadalbe string. 
	strcpy(str_arr, str_ptr);
	printf("Dotted-Decimal notation1: %s \n", str_ptr);	//1.2.3.4
	
	inet_ntoa(addr2.sin_addr);
	printf("Dotted-Decimal notation2: %s \n", str_ptr);//1.1.1.1
	//printf("Dotted-Decimal notation3: %s \n", str_arr);//1.2.3.4 duplicate sentence




	
	struct sockaddr_in newAddr;				//c가 객체지향이 아니라 structure 로부터 변수 생성
	newAddr.sin_addr.s_addr = htonl(0x06070809);
	str_ptr = inet_ntoa(newAddr.sin_addr);
	printf("\nA new addr : %s \n", str_ptr);




	return 0;
}
