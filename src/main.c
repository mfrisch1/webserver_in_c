#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 8080 // Client will send data to this port

int main() {
	/* 
	 * Basic Server Side Socket Process 
	 * 1. Create socket 
	 * 2. Bind socket (naming a socket)
	 * 3. Listen to oncoming request
	 * 4. Accept or reject to request
	 * 5. Communicate using socket 
	 * 6. Close Connection
	 */


	// Create socket using socket system call 
	// https://man7.org/linux/man-pages/man2/socket.2.html
	// AF_INET							IPv4 Internet protocols
	// SOCKET_STREAM				Reliable, two-way, byte stream
	int tcp_socket_fd;
	if ((tcp_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Could not create socket");
		return 0;
	}

	// Naming a socket; Assigning a port number -> binding an addr
	// https://man7.org/linux/man-pages/man2/bind.2.html
	// using bind system call
	// bind(int socket, const struct sockaddr *address, socklen_t address_len);
	// sockaddr							generic container, use struct sockaddr_in from netinet/in.h for IP networking 
	struct sockaddr_in addr; // IPv4 addr structure
	memset((char *)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	// INADDR_ANY						(0.0.0.0), means any address for socket binding
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // host to network type long int
	addr.sin_port = htons(PORT);

	if (bind(tcp_socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind failed");
		return 0;
	}

	// listen for incoming connection
	if (listen(tcp_socket_fd, 3) < 0) {
		perror("In listen");
		exit(EXIT_FAILURE);
	}

	// Create new socket fd for accepted request.
	int new_tcp_socket_fd;
	int addrlen = sizeof(addr);
	if ((new_tcp_socket_fd = accept(tcp_socket_fd, (struct sockaddr *)&addr, (socklen_t *)&addrlen)) < 0) {
		// 2nd paramater: Address structure that gets filed in with the address of the client that is doing the connect.
		perror("In accept");
		exit(EXIT_FAILURE);
	}

	// Send and Recieve message
	// since socket is a file desciptor to a file, write and read system call that works on file works on sockets
	char buff[1024] = {0};
	int valread = read( new_tcp_socket_fd, buff, 1024);
	printf("%s\n", buff);
	if (valread < 0) {
		printf("No byte are there to read");
	}
	
	char *hello = "Hello from the server!";
	write(new_tcp_socket_fd, hello, strlen(hello));
	
	// close the connection
	close(new_tcp_socket_fd);

	return 0;
}
