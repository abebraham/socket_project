#include <stdio.h>
#include <errno.h>
#include <netinet/in.h> 
#include <netdb.h> 
#include "vector.h"

#define DATA_BUFFER "Mona Lisa was painted by Leonardo da Vinci"

int main(int argc, char *argv[] ){
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
		return -1;
	} 
	//vector_print( &vec );

	struct sockaddr_in saddr;
	int fd, ret_val;
	struct hostent *local_host; /* need netdb.h for this */

	/* Step1: create a TCP socket */
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
	if (fd == -1) {
	 fprintf(stderr, "socket failed [%s]\n", strerror(errno));
	 return -1;
	}
	printf("Created a socket with fd: %d\n", fd);

	/* Let us initialize the server address structure */
	saddr.sin_family = AF_INET;         
	saddr.sin_port = htons(7000);     
	local_host = gethostbyname("127.0.0.1");
	saddr.sin_addr = *((struct in_addr *)local_host->h_addr);

	/* Step2: connect to the TCP server socket */
	ret_val = connect(fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));
	if (ret_val == -1) {
	 fprintf(stderr, "connect failed [%s]\n", strerror(errno));
	 close(fd);
	 return -1;
	}
	printf("The Socket is now connected\n");

	printf("Let us sleep before we start sending data\n");
	sleep(5);

	/* Next step: send some data */
	ret_val = send(fd,vec.data, vec.size * sizeof(vec.data), 0);
	printf("Successfully sent data (len %d bytes): %ld\n", ret_val, vec.size * sizeof(vec.data));

	/* Last step: close the socket */
	vector_free( &vec ); // free vector array
	close(fd);
	return 0;
}
