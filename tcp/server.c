#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
void func(char *str)
{
	int i = 0;
	str[0] = '0';
	while((str[i+1]!='\n')&&(str[i+1]!='\0')) i++;
	str[i] = '0';
}
int main()
{
	int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int clfd;
	struct sockaddr_in serv, cl;
	char buff[256];
	int cl_size = sizeof(cl);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(5560);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(fd, (struct sockaddr*) &serv, sizeof(serv));
	listen(fd,5);
	while(1)
	{
		cl_size = sizeof(cl);
		clfd = accept(fd,(struct sockaddr*) &cl, &cl_size);
		recv(clfd, buff, 256, 0);
		if (!strcmp(buff, "shutdown\n")) break;
		func(buff);
		send(clfd, buff, 256, 0);
		close(clfd);
	}
	close(clfd);
	close(fd);
	return 0;
}
