

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // for the structures
#include <errno.h> // for perror
#include <fcntl.h> // for open
#include <unistd.h> // for close
// for inet_ntohs
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int check_func_name(char *str){
	
	const char* func[4];
	func[0] = "max";
	func[1] = "min";
	func[2] = "sqr";
	func[3] = "sos";
 	
	short i = 0;
	for(i; i < 4; ++i){
		if( strcmp(str,func[i]) == 0){
			printf("%d\n",i);
			return i; 
		}
	}
	return -1;
}


int main(int argc, char *argv[] ){
	// check that terminal includes function name
	if( argc == 1 ){
		printf("Invalid Argument\n->Please add function name\n");
		exit(-1);
	}
	else if( check_func_name(argv[1]) < 0){
		printf("Please select from: 'min', 'max', 'sqr', or 'sos'\n");
		exit(-1);	
	}	
	else{
		printf( "Successful argument!\n%s : %d\n",argv[1], check_func_name(argv[1]) );	
	}
	

	int sock, cli;
	struct sockaddr_in server, client;
	unsigned int len;
	char mesg[] = "Hello world!\n";
	int sent; // number of bytes from sent
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1){
		perror("socket");
		exit(-1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(10005);
	server.sin_addr.s_addr = INADDR_ANY; // all avail interf on machine
	bzero(&server.sin_zero, 0);	
	
	len = sizeof(struct sockaddr_in);
	if( (bind(sock, (struct sockaddr *)&server, len) == -1) ){
		perror("bind");
		exit(-1);
	}

	if( listen(sock, 5) == -1 ){
		perror("listen");
		exit(-1);
	}

	while(1){
		if( (cli = accept(sock, (struct sockaddr*)&client, &len)) == -1 )
		{
			perror("accept");
			exit(-1);	
		}
		sent = send(cli, mesg, strlen(mesg), 0);
		printf("Sent %d bytes to client : %s\n", sent, inet_ntoa(client.sin_addr));
		close(cli);
	}
} 


