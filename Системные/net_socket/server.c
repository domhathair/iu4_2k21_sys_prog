#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

void main()
{
	struct sockaddr_in server;
	char buffer[24] = {0};
	char time_s[10] = {0, 0, 0, 0, 0, 0, 0, 0, '.', '\n'};

	int socket_fd = socket(AF_INET, SOCK_STREAM, 0); //-1 for error
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(2306);

	bind(socket_fd, (struct sockaddr *)&server, sizeof(server));
	listen(socket_fd, 0);

	time_t tick = time(NULL);
	char *string = ctime(&tick);
	for (int i = 0; i < 8; i++)
		time_s[i] = *(string + i + 11);
	printf("Server started at %s", time_s);
	int new_socket_fd = -1;
	int count = 0;

	while (1)
	{
		new_socket_fd = accept(socket_fd, (struct sockaddr *)NULL, NULL);
		if (new_socket_fd > 0)
		{
			tick = time(NULL);
			string = ctime(&tick);
			for (int i = 0; i < 8; i++)
				time_s[i] = *(string + i + 11);
			count++;
			printf("Connection #%d has arrived at %s", count, time_s);
			sprintf(buffer, "Works fine at %s", time_s);
			write(new_socket_fd, buffer, strlen(buffer));
			memset(buffer, 0, sizeof(buffer));
			close(new_socket_fd);
		}
		new_socket_fd = -1;
	}
	close(socket_fd);
}
