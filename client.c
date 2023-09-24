#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // For inet_pton
#include <unistd.h> // For close()

#define SERVER_PORT 9999
#define MAX_LINE 256

int main(int argc, char *argv[]) {

    struct sockaddr_in sin;
    char *host;
    char buffer[MAX_LINE];
    int s = 0;

    if (argc == 2) {
        host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s <IP Address>\n", argv[0]);
        exit(1);
    }

    memset((char *)&sin, 0, sizeof(sin));
    sin.sin_family = PF_INET;
    // convert network byte order
    sin.sin_port = htons(SERVER_PORT);
    
    // create socket descriptor (PF_INET + SOCK_STREAM = TCP protocol)
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(1);
    }
    
    // connect to remote server
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("Connection Failed");
        close(s);
        exit(1);
    }
    
    while (1) {
        printf("Enter something (Ciao-Ciao to exit): ");
        memset(buffer, 0, sizeof(buffer));

        // read the input into the buffer
        fgets(buffer, MAX_LINE, stdin);
        
        // send buffer to the server
        int isWrote = write(s, buffer, strlen(buffer));
        if (isWrote < 0) {
            perror("Error writing to socket");
            break;
        }

        // if the input is "Ciao-Ciao" then close the connection
        if (strcmp(buffer, "Ciao-Ciao\n") == 0) {
            printf("Closing connection...\n");
            break;
        }

        memset(buffer, 0, sizeof(buffer));

        // read the server response into the buffer
        int valread = read(s, buffer, MAX_LINE);
        if (valread < 0) {
            perror("Error reading from socket");
            break;
        }

        buffer[valread] = '\0';
        printf("Server response: %s", buffer);
    }
    
    // close socket descriptor
    close(s);
    exit(0);
}