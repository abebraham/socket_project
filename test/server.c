#include <stdio.h>
#include <errno.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 

#define DATA_BUFFER 300

int create_tcp_server_socket() {
	struct sockaddr_in saddr;
	int fd, ret_val;

	/* Step1: create a TCP socket */
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
	if (fd == -1) {
		fprintf(stderr, "socket failed [%s]\n", strerror(errno));
		close(fd);
		return -1;
	}
	printf("Created a socket with fd: %d\n", fd);

	/* Initialize the socket address structure */
	saddr.sin_family = AF_INET;         
	saddr.sin_port = htons(7000);     
	saddr.sin_addr.s_addr = INADDR_ANY; 

	/* Step2: bind the socket to port 7000 on the local host */
	ret_val = bind(fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));
	if (ret_val != 0) {
		fprintf(stderr, "bind failed [%s]\n", strerror(errno));
		close(fd);
		return -1;
	}

	/* Step3: listen for incoming connections */
	ret_val = listen(fd, 5);
	if (ret_val != 0) {
		fprintf(stderr, "listen failed [%s]\n", strerror(errno));
		close(fd);
		return -1;
	}
	return fd;
}

int main () {
	struct sockaddr_in new_client_addr;
	int fd, new_fd, ret_val, index;
	socklen_t addrlen;
	long buf[300];

	/* Create the server socket */
	fd = create_tcp_server_socket(); 
	if (fd == -1) {
		fprintf(stderr, "Creating server failed [%s]\n", strerror(errno));
		return -1;
	}

	/* Accept a new connection */
	new_fd = accept(fd, (struct sockaddr*)&new_client_addr, &addrlen);
	if (new_fd == -1) {
		fprintf(stderr, "accept failed [%s]\n", strerror(errno));
		close(fd);
		return -1;
	}
	printf("Accepted a new connection with fd: %d\n", new_fd);

	/* Receive data */
	printf("Let us wait for the client to send some data\n");
	do {
		ret_val = recv(new_fd, buf, DATA_BUFFER*4, 0);
		printf("Received data (len %d bytes)\n", ret_val);
		if (ret_val > 0) 
			//printf("Received data: %ld\n", buf[0]);
			index = 0;
			while(index < ret_val){
				printf("%d: %ld\n",index, buf[index++]);
			}
		if (ret_val == -1) {
			printf("recv() failed [%s]\n", strerror(errno));
			break;
		}
	}while (ret_val != 0);

	/* Close the sockets */
	close(fd);
	close(new_fd);
	return 0;
}
