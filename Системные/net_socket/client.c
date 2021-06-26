#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void main()
{
	int socket_fd = -1; //-1 for error
	char buffer[24] = {0};
	struct sockaddr_in server;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;					 //ip protocol family
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(2306);

	if (!connect(socket_fd, (struct sockaddr *)&server, sizeof(server)))
	{
		read(socket_fd, buffer, sizeof(buffer) - 1);
		printf("%s\n", buffer);
		close(socket_fd);
	}
	else
		printf("Server shutted down.\n");
	exit(0);
}
