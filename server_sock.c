#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>

#define MYPORT 12217
#define MAX_CONN 5
int main()
{
	int serverfd = 0 , clientfd = 0;
	struct sockaddr_in serveraddr , cliaddr;
	int num = 0;
	int num2 =0;

	serverfd = socket(AF_INET , SOCK_STREAM , 0);
	if(serverfd == -1 )
	{
		printf("error in opening socket\n");
		exit(1);
	}
	memset(&serveraddr , 0 , sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(MYPORT);

	if(bind(serverfd ,(struct sockaddr*) &serveraddr , sizeof(serveraddr)) != 0)
	{
		perror("bind error");
		exit(1);
	}

	if(listen(serverfd , MAX_CONN )!= 0 )
	{
		perror("error in  listen");
		exit(3);
	}

	int len = sizeof(cliaddr);
	clientfd = accept(serverfd , (struct sockaddr*)&cliaddr , &len);
	if(clientfd < 0)
	{
		perror("accept error");
		exit(4);
	}

	do{
		num++;
		send(clientfd ,  &num , sizeof(num) , 0);
		if(recv(clientfd , &num2 , sizeof(num2), 0) <=0 )
		{
			perror("recv error");
			close(clientfd);
			break;
		}
		else
		{
			printf("received %d\n", num2);
		}

	}while(1);

}
