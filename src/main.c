#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

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
	struct sockaddr_in addr;
	
	return 0;
}
