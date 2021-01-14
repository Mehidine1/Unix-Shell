
Operating Systems Project

Phase 3 Report-Upgrading the remote shell to a remote multitasking shell




11/4/2020


The linux shell or Bash Shell, which is a command line interface provides us with simple commands that allow us to gain more control of our system and become more productive.
The G23shell implemented process creation by the use of the fork system call, where we forked a child to have the user input the data, and then this data was compared to what our shell has to offer. If the data matched one of our methods, exec function was called and its result was communicated to the parent using pipes which then parsed the result into a string and printed it on the shell. Pipes were also used for commands with pipes inside them, where the output of one command is the input of the next one. Shared memory was also used to keep track whether the processes should break from the infinite while loop and terminate the program if the exit command was executed. Thus, the concepts of inter process communication and process creation were used heavily to implement phase 1.


Our G23shell will provide you with 13 commands, including several functionalities:

	Knowing current directory information:
-lfiles, lfiles -l.
-pdirectory.

		Help
-listcommands

		Knowing processes information:
-lprocesses.
-lrunningps.

		Stop execution:
-exit.

		Printing the current date:
-date.

		Network information:
-netstat

	2 single piped commands:
-Lfiles| wc –w
	-lfiles -al|more
	1 double piped command:
-lprocesses|grep shell|wc -l

	Display the total memory used:
-dmemory

Knowing the current directory information:
Modern filesystems have directory (folder) trees, where a directory is either a root directory (with no parent directory) or is a subdirectory (contained within a single other directory, which we call its "parent"). 
When working within a filesystem, the user is always working within some directory, suppose the user wants to know what files are present in the CURRENT directory he’s working in. Our G23 shell provides an lfiles command that will allow the user to quickly view all files within the specified directory:
-lfiles: list the content of the current working directory in regular format.
 
-lfiles -l: Will display the content of the current working directory in long listing format, printing the name of the file, the owner and permissions.
 

Our G23 shell will provide a pdirectory command that will print the current directory the user is working in. As an example, if a user has multiple terminals going and the user needs to remember the exact directory he’s/she’s working within, then pdirectory will tell him\her.
 


-Help:
If a user needs to know the list of commands and their functions, our G23 shell provides him with a listcommands command that will print the commands and their functions as shown:
 

Knowing processes information:
A process is basically a single running program. It may be a "system" program (e.g login, update, csh) or program initiated by the user,  When we run a process the OS gives each process a unique number - a process ID, pid along with other attributes assigned to it..
The lprocesses command will for print information related with the processes on a system. lprocesses command is used to list the currently running processes and their PIDs along with some other information…
 
PID – the unique process ID
TTY – terminal type that the user is logged into
TIME – amount of CPU in minutes and seconds that the process has been running
CMD – name of the command that launched the process.
The lrunningps command has the same functionality of lprocesses but will only print information about currently running processes.
 

Stop execution:
Let’s suppose that a user ran into an error while working, our G23shell provides him with an exit command that’ll stop execution…
 

Network information:
netstat is a command that can be used to list out all the network (socket) connections on a system. It lists out all the tcp, udp socket connections and the unix socket connections. Apart from connected sockets it can also list listening sockets that are waiting for incoming connections.
 

Printing the current date:
date command is used to display the system date and time.
 

Single Piped commands:
-lfiles| wc –w
the lfiles list all the files in the current directory, this list would become the input that the wc –w command takes, which checks the number of words of this input. Thus this piped command returns the number of files inside the current directory since it returns the number of words(file names)  of the lfiles command.
 

- lfiles -al | more
-There are a few entries in some ls listings that you may not care about. For instance, the metacharacters . and .. represent "here" and "back one level," respectively. If you're familiar with navigating in a terminal, you probably already know that each directory refers to itself as . and to its parent as .., so you don't need to be constantly reminded of it when you use the -a option to show hidden files, we use -a option to show these hidden files…
-The morecommand helps us navigate outputs from commands in a user-friendly way.
The lsfiles -al will display the content of the current working directory in long listing format, printing the name of the file, the owner and permissions in addition to the hidden files due to the use of -a. this list would become the input that the more command takes, Thus this piped 
lfiles -al | more command returns the content of the current working directory in long listing format, printing the name of the file, the owner and permissions in addition to the hidden files, all in a user friendly way to navigate the list through ENTER key, SPACEBARwhen doing froward scrolling, and backward scrolling using b.
 

Double piped command: 
lprocesses|grepshell|wc –l
the lprocesses lists the processes and the output then becomes the input of the grep shell command which lists the lines the shell word was found in and this output becomes the input of the wc –l command which then return the number of lines the shell command was found in.Thus, this command returns the number of lines the shell word is found in the processes.
 



Display the total memory used:
-dmemory will display the estimated memory the directory uses along with each file in it.
 



PHASE 2:
We upgraded our phase1 G23 shell to include remote access capability through socket communication. the client takes inputs from the user and sends requests to the server. Each input from the client is a command from our commands list. The client will then receive the output/result from the server and print it on the screen.
Screenshots:
The screenshots taken of our running code shows the remote shell executing various formats while taking inputS from one client, to stop execution and close both the client and server socket, we implemented an exit function(shown in the screenshot below and code included).

 
 
 
 
 
 
 
in the figures above, we run our various commands to ensure everything is working, at the end we use our exit, it shows that both client and server stop executing .


PHASE3:
We upgraded our remote shell to become a multitasking remote shell by allowing multiple clients to connect to one server and creating a thread for each client that takes the basic parameters in addition to a method void* ThreadRun (void * socket) that takes the client socket as parameter and handles the read/write operations between each client and server alone.
Details of the code are found in the zip file, screenshot of the running code is provided below.
 
# Unix-Shell
Multitasking Remote Unix shell
