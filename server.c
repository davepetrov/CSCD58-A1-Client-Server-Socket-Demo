#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>

#define SERVER_PORT 9999
#define MAX_LINE 256
#define MAX_PENDING 5

int main() {
    int s, client_fd;
    struct sockaddr_in sin;
    char buffer[MAX_LINE];

    // Initialize sin memory
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);
    
    // create socket descriptor (PF_INET + SOCK_STREAM = TCP protocol)
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(1);
    }
    
    // associate the local address
    if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("bind failed");
        exit(1);
    }
    
    // wait for incoming connections from clients
    listen(s, MAX_PENDING);
    
    printf("Server is listening on port %d\n", SERVER_PORT);
    
    // Main loop for accepting incoming connections
    while (1){
        socklen_t len = sizeof(sin);
        // accept incoming connection
        if ((client_fd = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
            perror("accept");
            exit(1);
        }
        printf("Client connected\n");
        
        // Loop for handling client data
        while (1) {
            // reset the buffer
            memset(buffer, 0, sizeof(buffer));

            // read the input from the client, put into buffer
            int valread = read(client_fd, buffer, MAX_LINE);
            if (valread < 0) {
                perror("Error reading from socket");
                break;
            }
            buffer[valread] = '\0';
            
            // if the input is "Ciao-Ciao" then close the connection
            if (strcmp(buffer, "Ciao-Ciao\n") == 0) {
                printf("Client disconnected using prompt. Closing connection...\n");
                break;
            }
            
            time_t now;
            time(&now);
            char* datetime = ctime(&now);
            char response[MAX_LINE];
            snprintf(response, sizeof(response), "%s%s", buffer, datetime);
            
            // send response back to client
            write(client_fd, response, strlen(response));
        }
        break;
    }
    
    // close the server socket file descriptor
    close(client_fd);
    close(s);
    exit(0);
}