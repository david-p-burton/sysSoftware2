// server code

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
	int welcomeSocket, newSocket;
	int readSize;
	char buffer[1024];
	char writeBuffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	// create socket
	// internet domain, stream socket, default protocol (TCP)
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

	if(welcomeSocket == -1)
	{
		printf("Socket could not be created.\n");
	}
	else
	{
		printf("Socket created\n");
	}

	//configure settings of server address struct
	serverAddr.sin_family = AF_INET;
	// port number using htons func
	serverAddr.sin_port = htons(8081); //may need to change port number
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	// bind address struct to socket
	if(bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("Error on binding.");
	}

	// listen on socket
	if(listen(welcomeSocket, 10) == 0)
	{
		printf("Listening...\n");
	}
	else
	{
		printf("Listening error!\n");
	}

	addr_size = sizeof(serverStorage);
	newSocket = accept(welcomeSocket, (struct sockaddr *) & serverStorage, &addr_size);

	if(newSocket < 0)
	{
		perror("Can't establish a connection.");
		return 1;
	}
	else
	{
		printf("\nAccepted.\n");
	}


	while(1)
	{
		readSize = recv(newSocket, buffer, 1024, 0);
		printf("Client message: %s", buffer);
		fgets(writeBuffer, 1024, stdin);
		write(newSocket, writeBuffer, 1024);

		if( readSize == 0 )
		{
			puts("Client disconnected");
			fflush(stdout);
		}
		else if (readSize == -1)
		{
			perror("Read ERROR.");
		}
	}


	return 0;

}





