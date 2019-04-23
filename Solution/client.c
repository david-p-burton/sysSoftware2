// client code

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

char* serverDirectories(char* index)
{

	// 1 - root
	// 2 - Sales
	// 3 - Promotions
	// 4 - Offers
	// 5 - Marketing

	char addr[1024] = "/home/david/sysSoftware2/website/";

	if(strcmp(index, "1") ==0)
	{
		return addr;
	}
	if(strcmp(index, "2") ==0)
	{
		strcat(addr, "Sales/");
		return addr;
	}
	if(strcmp(index, "3") ==0)
	{
		strcat(addr, "Promo/");
		return addr;
	}
	if(strcmp(index, "4") ==0)
	{
		strcat(addr, "Offers/");
		return addr;
	}
	if(strcmp(index, "5") ==0)
	{
		strcat(addr, "Marketing/");
		return addr;
	}
}

int main()
{
	int clientSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	// create socket
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	// settings of server address struct
	serverAddr.sin_family = AF_INET;
	// port number using htons func
	serverAddr.sin_port = htons(8081); //may need to change port number
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	// connect socket to server using address struct
	addr_size = sizeof(serverAddr);
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

	// read the message from the server to buffer
	recv(clientSocket, buffer, 1024, 0);

	// print received message
	printf("Data received: %s", buffer);

	for(int i = 0; i < 6; i++)
	{
		
	}

	return 0;
}