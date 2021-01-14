#include <unistd.h>

#include <stdio.h>

#include <sys/socket.h>

#include <stdlib.h>

#include <netinet/in.h>

#include <string.h>

#include <wait.h>

#include <pthread.h>

#include <sys/mman.h>



#define PORT 6500

#define MAXLINE 1000



void* ThreadRun (void*);



int main(int argc, char const *argv[])

{


	printf("(っ◔◡◔)っ ♥ If you want to know more about commands, use listcommands.\nDon't forget to use the exit command to stop execution and close the sockets.\nThank you ♥\n");


	int server_socket = 0, client_socket = 0;

	struct sockaddr_in address;

	int opt=1;

	int addrlen=sizeof(address);

	if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0){

		perror("failed\n");

		exit(1);

	}

	if(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){

		printf("failed");

		exit(1);

	}



	address.sin_family= AF_INET;

	address.sin_addr.s_addr= INADDR_ANY;

	address.sin_port=htons(PORT);



	if(bind(server_socket, (struct sockaddr *)&address,sizeof(address)) <0){

		printf("failed\n");

		exit(1);

	}

while(1)

{

	if(listen(server_socket, 5)<0){

		printf("failed\n");

			exit(1);

	}



if((client_socket=accept(server_socket,(struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0){

	printf("failed\n");

	exit(1);

}


	

	pthread_t th;

        pthread_attr_t attr;

        pthread_attr_init(&attr);

        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_create(&th,&attr,ThreadRun,&client_socket);

}



	close(server_socket);


	return 0;

}

void* ThreadRun (void * socket){

 int *sock=(int*)socket;

        int s=*sock;



	while(1){



       

	int* EXIT = (int*) mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);

	char buffer[500]= {0};

	char text[5000]= {0};

 	int* output = (int*) mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);

	output[0] = 0;



read(s,buffer,sizeof(buffer));



	int fd[2];

	int help[2];

	pipe(help);

    	pipe(fd);

    	pid_t pid = fork();

 if (strcmp(buffer,"listcommands")==0){

		close(help[0]);

	char listcom[] = "\nlfiles: list the content of the current working directory in regular format.\nlfiles -l: display the content of the current working directory in long listing format,\nprinting the name of the file, the owner and permissions.\nlfiles -al|more: display part of the information of current working directory content in long listing format.\nlfiles|wc -w: return the number of files in current working directory.\nlprocesses: print information related with the processes on the system.\nlrunningps: print information related with the RUNNING processes on the system.\nlprocesses|grep shell|wc -l: prints the number of times shell was found in the processes' information.\ndmemory: estimates the total memory the directory uses along with each file in it.\npdirectory: print the current directory the user is working in.\nnetstat: list out all the network (socket) connections on a system.\ndate: display the system date and time.\nexit: stop execution.\n\n";

		write(help[1], listcom, sizeof(listcom));

		close(help[1]);

	output[0] = 1;

		}

 if (strcmp(buffer,"exit") !=0 && strcmp(buffer,"lfiles -l") !=0&&strcmp(buffer,"lprocesses|grep shell|wc -l") != 0&&strcmp(buffer, "lfiles -al|more") != 0&&strcmp(buffer, "lfiles|wc -w") != 0&&strcmp(buffer,"lfiles")!=0&&strcmp(buffer,"listcommands")!=0&&strcmp(buffer,"lprocesses")!=0 &&strcmp(buffer,"date")!=0 &&strcmp(buffer,"dmemory")!=0&&strcmp(buffer,"netstat")!=0&&strcmp(buffer,"pdirectory")!=0&&strcmp(buffer,"lrunningps")!=0){

		close(help[0]);

		char nocom[] = "There is no such command. Enter listcommands for the list of commands.\n";

		write(help[1], nocom, sizeof(nocom));

		close(help[1]);

	output[0] = 1;

		}



      if (pid ==0){

	close(fd[0]);

	dup2(fd[1],1);

	close(fd[1]);

	if(strcmp(buffer, "lprocesses") == 0){

	

	execl("/bin/ps","ps",NULL);



		}



	else if(strcmp(buffer, "lrunningps") == 0){

	

		execlp("ps","ps","-r", NULL);



		}







	else if (strcmp(buffer,"lfiles") ==0){



	execl("/bin/ls","ls",NULL);

	}

	

	else if (strcmp(buffer,"lfiles -l") ==0){



	execlp("ls", "ls", "-l", "/", NULL);

	

	}





	else if(strcmp(buffer, "pdirectory") == 0){



	execl("/bin/pwd", "pwd", NULL);

	



		}

	



	if(strcmp(buffer, "exit") == 0){

		

		close(fd[0]);

		close(fd[1]); 

		close(help[0]);

		close(help[1]); 

		EXIT[0]=1;

		break;

		}

	



	else if(strcmp(buffer, "netstat") == 0){

	

	execl("/bin/netstat", "netstat", NULL);

	



		}

	else if(strcmp(buffer, "dmemory") == 0){

	

	execl("/bin/du", "du","-ah", NULL);

	



		}



	else if(strcmp(buffer, "date") == 0){

	



	execl("/bin/date", "date", NULL);

	



		}



	else if(strcmp(buffer, "lfiles|wc -w") == 0){

		int fd1[2];

        	pipe(fd1);      

			pid_t pid1 =fork();  

	        if(pid1 == 0) {

         close(fd1[0]);

	dup2(fd1[1],1);

	close(fd1[1]);

           execl("/bin/ls","ls",NULL);

        }

	else if(pid1 > 0){

      wait(NULL);	

      close(fd1[1]);

	dup2(fd1[0],0);

	close(fd1[0]);

          execl("/bin/wc","wc","-w",NULL);

}

        close(fd1[0]);

        close(fd1[1]);

  

		}



else if(strcmp(buffer, "lfiles -al|more") == 0){

		int fd2[2];

        	pipe(fd2);      

			pid_t pid2 =fork();  

	        if(pid2 == 0) {

         close(fd2[0]);

	dup2(fd2[1],1);

	close(fd2[1]);

           execl("/bin/ls","ls","-al",NULL);

        }

	else if(pid2 > 0){

      wait(NULL);	

      close(fd2[1]);

	dup2(fd2[0],0);

	close(fd2[0]);

          execl("/bin/more","more",NULL);

}

        close(fd2[0]);

        close(fd2[1]);

  

		}

else if(strcmp(buffer,"lprocesses|grep shell|wc -l") == 0){

		int fd3[2];

	

        	pipe(fd3); 

		   

		pid_t pid3 =fork();  

	        if(pid3 == 0) {	

		int fd4[2];

		pipe(fd4);  

               pid_t pid4 = fork();

	if(pid4== 0){

         close(fd4[0]);

	dup2(fd4[1],1);

	close(fd4[1]);

           execl("/bin/ps","ps",NULL);

}

	else if(pid4>0){

      wait(NULL);	

      close(fd4[1]);

	dup2(fd4[0],0);

	close(fd4[0]);

       

       close(fd3[0]);

	dup2(fd3[1],1);

	close(fd3[1]);

          execl("/bin/grep","grep","shell",NULL);

}

        }

	else if(pid3 > 0){

wait(NULL);

close(fd3[1]);

	dup2(fd3[0],0);

	close(fd3[0]);



 execl("/bin/wc","wc","-l",NULL);



}

        close(fd3[0]);

        close(fd3[1]);



		}

}



     else if (pid>0){

	waitpid(pid,NULL,0);



	close(fd[1]);

	close(help[1]);	

	char text[10000];

	if (output[0] == 0){

	read(fd[0],text,sizeof(text));

	send(s,text,strlen(text),0);

}	else{

	read(help[0],text,sizeof(text));

	send(s,text,strlen(text),0);

} 

	memset(text,0,10000);

	output[0] =0;

	output[1] = 0;



	if(EXIT[0] == 1){

	close(s);

	break;

}



	}









close(fd[0]);

close(fd[1]); 

close(help[0]);

close(help[1]); 



}





close(s);

}