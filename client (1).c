#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

#define MAXLINE 1000
#define PORT 6500

int main()
{
	int client_socket;
	struct sockaddr_in serv_addr;
	if( (client_socket=socket(AF_INET, SOCK_STREAM, 0)) <0 ){
		printf("failed\n");
		exit(1);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port=htons(PORT);

	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){

		printf("Invalid address\n");

		return -1;
	}

	if(connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <0 ){

		printf("Connection failed\n");
		return -1;
	}


while(1){
char buffer[500];
char s2[10000] = {0};
printf("shell/:");
fgets(buffer,sizeof(buffer),stdin);
fflush(stdin);
strtok(buffer,"\n");
if (strcmp(buffer, "exit") == 0){
close(client_socket);
break;
}


send(client_socket,buffer,strlen(buffer),0);
read(client_socket,s2,sizeof(s2));
printf("%s\n",s2);
memset(buffer,0,500);



}


close(client_socket);
return 0;
}