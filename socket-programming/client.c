#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

//#define DATA "Hello World of socket"

using namespace std;

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in server;
	struct hostent *hp;
	char buff[1024];
	string data;
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket failed");
		exit(1);
	}
	
	server.sin_family = AF_INET;
	
	hp = gethostbyname(argv[1]);
	if(hp == 0)
	{
		perror("gethostbyname failed");
		close(sock);
		exit(1);	
	}
	
	memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
	server.sin_port = htons(5000);
	
	if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
	{
		perror("connect failed");	
		close(sock);
		exit(1);
	}

	
	while(1)
	{
	cin >> data;	
		if(send (sock, data, sizeof(data), 0) < 0)
		{
		perror("send failed");
		close(sock);
		exit(1);
		}
		printf("Send %s\n", data);
		
		if( data == "exit" )
		{
			break; 
		}
	}
	close(sock);
	return 0;
}



