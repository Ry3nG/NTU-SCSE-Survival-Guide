#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

struct hostent *server;
int port;

void error(char *msg){
    perror(msg);
    exit(1);
}

void handle_input(){
    char buffer[256];
    int n;
    struct sockaddr_in serv_addr;

    // create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("Error opening socket");

    memset((char *) &serv_addr, 0, sizeof(serv_addr));

    //set address family
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    // connect to the server
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("Error connecting");

    int number = (rand()*getpid()) % 100;
    sprintf(buffer, "%d", number);

    printf("Client request: %s\n", buffer);

    // write to the server
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) error("Error writing to socket");

    // read from the server
    memset(buffer, 0, sizeof(buffer));
    n = read(sockfd, buffer, 255);
    if (n < 0) error("Error reading from socket");

    printf("Server response: %s\n", buffer);

    close(sockfd);
}

int main(int argc, char *argv[]){
    srand(time(NULL));

    if (argc < 3){
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    port = atoi(argv[2]);
    server = gethostbyname(argv[1]);

    if (server == NULL){
        fprintf(stderr, "Error, no such host\n");
        exit(0);
    }

    // fork into three child processes to handle user input
    int i;
    for (i = 0; i < 3; i++){
        pid_t pid = fork();
        if (pid < 0) error("Error on fork");
        if (pid == 0){
            handle_input();
            exit(0); 
        
        }

        usleep(1000000); // sleep for 1 second
    }

    for (i = 0; i < 3; i++){
        wait(NULL);
    }

    return 0;
}