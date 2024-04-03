#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>

sem_t empty;
sem_t full;
pthread_mutex_t mutex;
int client_buffer[10];
int in = 0;
int out = 0;

void error(char *err_msg){
    perror(err_msg);
    exit(1);
}

void *handle_client(void *arg){
    int newsockfd = *((int *)arg);
    char buffer[256];
    int n;

    n = read(newsockfd, buffer, 255);
    if (n < 0) error("Error reading from socket");

    printf("Client request: %s\n", buffer);
    int number = atoi(buffer);

    memset(buffer, 0, sizeof(buffer)); // Clear buffer for server response
    sprintf(buffer, "Server received: %d", number*5);

    sem_wait(&empty); // Wait for an empty slot
    pthread_mutex_lock(&mutex);
    client_buffer[in] = newsockfd;
    in = (in + 1) % 10;
    pthread_mutex_unlock(&mutex);
    sem_post(&full); // Signal that a slot has been filled

    sem_wait(&full); // Wait for a full slot
    n = write(newsockfd, buffer, strlen(buffer)); 
    if (n < 0) error("Error writing to socket");

    printf("Server response: %s\n", buffer);
    printf("client disconnected\n");

    sem_post(&empty); // Signal that a slot has been emptied

    close(newsockfd);
    pthread_exit(NULL);
}
int main(int argc, char *argv[]){
    int sockfd, newsockfd, port, client_len;
    struct sockaddr_in serv_addr, client_addr;

    if (argc < 2){
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) error("Error opening socket");

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("Error on binding");

    listen(sockfd, 3);

    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    while(1){
        client_len = sizeof(client_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_len);

        if (newsockfd < 0) error("Error on accept");

        pthread_t client_thread;
        pthread_create(&client_thread, NULL, handle_client, (void *)&newsockfd);
        pthread_detach(client_thread);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    close(sockfd);

    return 0;

}