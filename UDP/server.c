
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define CL_SIZE sizeof(cl)
void func(char *str)
{
	int i = 0;
	str[0] = '0';
	while((str[i+1]!='\n')&&(str[i+1]!='\0')) i++;
	str[i] = '0';
}
int main()
{
	int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	int clfd;
	struct sockaddr_in serv, cl;
	char buff[256];
	int cl_size = 0;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(5561);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(fd, (struct sockaddr*) &serv, sizeof(serv));
	while(1)
	{
		cl_size = sizeof(cl);
		recvfrom(fd, buff, 256, MSG_WAITALL, (struct sockaddr*) &cl, &cl_size);
		if(!strcmp(buff, "shutdown\n"))
		{
			strcpy(buff, "Server has been killed\n");
			sendto(fd, buff, 256, 0, (struct sockaddr*) &cl, CL_SIZE);
			break;
		}
		func(buff);
		sendto(fd, buff, 256, 0, (struct sockaddr*) &cl, CL_SIZE);
	}
	//close(clfd);
	close(fd);
	return 0;
}
