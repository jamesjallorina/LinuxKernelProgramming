#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	/* Variables */
	int sockid;
	struct sockaddr_in addrport;
	int mysock;
	char buff[1024];
	int rval;
	
	
	/* Create socket */
	sockid = socket(PF_INET, SOCK_STREAM, 0);		//PF_INET: IPv4 protocol, internet address
	if(sockid < 0)
	{
		perror("Failed to create socket");
		exit(1);
	}
	
	server.sin_family = PF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(5100);
	
	
	/* Call bind */
	if( bind(sockid, (struct sockaddr *)&addrport, sizeof(addrport)) != -1)
	{
		printf("interface is good!\n");
	}
	else
	{
		perror("bind failed\n");
		exit(1);
	}
	
	/* Listen */
	int status = listen(sock, 5);				// five connection
	if ( status != 0 )
	{
		perror("connection limit reached!\n");
	}
	
	/* Accept */	
	do
	{
		mysock = accept(sockid, (struct sockaddr *) 0, 0);
		if(mysock == -1)
		{	
			perror("accept failed");
		}
		else
		{
			memset(buff, 0, sizeof(buff));	
			if((rval = recv(mysock, buff, sizeof(buff), 0)) < 0) 
				perror("reading stream message error");
			else if ( rval == 0 ) 
				printf("Ending connection\n");
			else 
				printf("MSG: %s\n", buff);
				
			printf("Got the message ( rval = %d )\n", rval);
			close(mysock);
		}	
	}while(1);
	
	return 0;
}