#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
int main()
{
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(5560);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	int fd;
	char buff[256];
	fgets(buff, 256, stdin);
	while(strcmp(buff,"exit\n"))
	{
		fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if((connect(fd,(struct sockaddr* ) &serv, sizeof(serv)))!=-1)
		{
			send(fd, buff, 256, 0);
			recv(fd, buff, 256, 0);
			printf("%s",buff);
		}
		else
		{
			printf("Connection error\n");
		}
		close(fd);
		fgets(buff, 256, stdin);
	}
	return 0;
}
