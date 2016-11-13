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

#include "vector.h" // custom made vector 

#define ERROR -1
#define BUFFER 1024

// check for correct function name
int check_func_name(char *str){
	const char* func[4];
	func[0] = "min"; 
	func[1] = "max";
	func[2] = "sum";
	func[3] = "sos";
 	// loop through all 4 possible selections
	short i = 0;
	for(i; i < 4; ++i){
		if( strcmp(str,func[i]) == 0){
			return i; // return corresponding selection
		}
	}
	return -1; // return if incorrect selection
}

int main(int argc, char *argv[] ){	
	int sel;

	// check that terminal includes function name
	if( argc == 1 ){
		printf("Invalid Argument!\nPlease select from: 'min', 'max', 'sum', or 'sos'\n");
		exit(-1);
	}
	else if( check_func_name(argv[1]) < 0){
		printf("Please select from: 'min', 'max', 'sum', or 'sos'\n");
		exit(-1);	
	}	
	else{ 
		sel = check_func_name(argv[1]); // correct selection has been made
		//printf( "Successful argument!\n%s : %d\n",argv[1], sel );	
	}
	
	FILE *file;
	file = fopen("nums.csv", "r");
	char line[16]; // range -2,147,483,648 to +2,147,483,648 (max characters = 13 )
	
	Vector vec; // create new vector struct
	vector_init(&vec); // initialize vector, to be sent to server
	// Check the csv file was open
	if(file != NULL){
		while( fgets(line, 16, file) != NULL){
			vector_append( &vec,atoi(line) ); // append to vector, line by line
		} 
		//printf("%d\n", sizeof(vec) );
		//printf("something: %ld\n", vector_get( &vec, 200) );
		//vector_print(&vec);
	}
	else{
		printf("error opening file\n");
		vector_free( &vec ); // dynamically free vector
		exit(-1);
	}

	fclose(file);
	
	struct sockaddr_in remote_server; // remote server structure 
	int sock; // socket descriptor
	int len;
	int i;
	
	sock = socket(AF_INET, SOCK_STREAM, 0); // create socket to connect to remote server
	if(sock == ERROR){
		perror("server socket");
		exit(-1);
	}

	const char* PORT = "25515"; // Server TCP Port Number
	const char* IP = "127.0.0.1"; // IP address
	
	remote_server.sin_family = AF_INET;
	remote_server.sin_port = htons(atoi( PORT )); // Remote server port number
	remote_server.sin_addr.s_addr = inet_addr( IP ); // IP address
	bzero(&remote_server.sin_zero, 8);	
	
	if( connect( sock, (struct sockaddr *)&remote_server, sizeof(struct sockaddr_in) ) == ERROR ){
		perror("connect");
		exit(-1);
	}
	
	long output[BUFFER];
	long input[BUFFER];
	i = 0;
	for(i; i < vec.size; i++){
		*input = vector_get(&vec,i); 
		if( send(sock, input, BUFFER, 0) == ERROR ){
			perror("send"); exit(-1);
		}	
		//printf("%d : %ld : %d\n",i,*input,vec.size);
	}
	

	if( recv(sock, output, BUFFER, 0) == ERROR ){
		perror("recv"); exit(-1);
	}
	printf("%ld\n",*output);


	/*
	while(1){
		//fgets(input, BUFFER, stdin); // get user input
		input[0] = 'x';
		send(sock, input, strlen(input),0); // send input as is to remote server
		
		len = recv(sock, output, BUFFER, 0);
		output[len]='\0'; // set end as null to avoid crashes
		printf("%s\n",output);
		

	}*/
	close(sock);
} 






