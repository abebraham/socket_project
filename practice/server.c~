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

#include "vector.h"

#define ERROR -1
#define MAX_CLIENTS 2
#define MAX_DATA 1024

int main(int argc, char *argv[] ){
	struct sockaddr_in server, client; // server & client structure 
	int sock; // server socket descriptor
	int new; // client socket descriptor 
	int sockaddr_len = sizeof(struct sockaddr_in); // input for bind and accept calls
	int data_len;
	char data[MAX_DATA];
	
	// start the server process
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == ERROR){
		perror("server socket");
		exit(-1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(25515); // Server TCP Port Number
	server.sin_addr.s_addr = INADDR_ANY; // all avail interf on machine
	bzero(&server.sin_zero, 8);	
	
	if( (bind(sock, (struct sockaddr *)&server, sockaddr_len) == ERROR) ){
		perror("bind");
		exit(-1);
	}

	if( listen(sock, MAX_CLIENTS) == ERROR ){
		perror("listen");
		exit(-1);
	}
	
	long dat[MAX_DATA];
	long output[MAX_DATA];
	Vector vec; // create new vector struct
	vector_init(&vec); // initialize vector, to be sent to server
	
	while(1){
		new = accept(sock, (struct sockaddr*)&client, &sockaddr_len);
		if( new == ERROR ){
			perror("accept"); exit(-1);	
		}	
		printf("New client connected form Port #: %d and IP: %s\n", ntohs(client.sin_port), inet_ntoa(client.sin_addr));
	
		data_len = 1;
		while(data_len){	
			data_len = recv(new, dat, MAX_DATA, 0);
			if( data_len == ERROR){
				perror("recv"); exit(-1);
			}
			else{
				vector_append(&vec,*dat);
			}
		}

		printf("hello: %ld\n", vector_sos(&vec));
	
		*output = vector_sum( &vec );
		int sent = send(new,output,MAX_DATA, 0);
		if( sent == ERROR){
			perror("send"); exit(-1);
		}
		printf("sent: %d\n",sent);
		printf("Send msg: %ld\n", *output);
		printf("Client disconnected\n");
	
		close(new);
	}
	close(sock);
} 

/**
		// switch statement for functions (min, max, sum, and sos)
		switch(sel){
			case 0:
				printf( "MIN: %ld\n",vector_min( &vec ) );
				break;
			case 1:
				printf( "MAX: %ld\n",vector_max( &vec ) );
				break;
			case 2:
				printf( "SUM: %ld\n",vector_sum( &vec ) );
				break;
			case 3:
				pprintf( "SOS: %ld\n",vector_sos( &vec ) );
				break;
		}


**/


