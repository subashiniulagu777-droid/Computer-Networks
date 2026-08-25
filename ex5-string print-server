#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8558
#define BUFFER_SIZE 1024

/* Shared structure for standard communication */
struct Message
{
    char data[BUFFER_SIZE];
};

int main()
{
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    struct Message message;

    /* Create UDP socket */
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    /* Server address config */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    /* Bind socket */
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(server_socket);
        return 1;
    }

    printf("====================================\n");
    printf("          UDP SERVER\n");
    printf("====================================\n");
    printf("Server started on port %d\n", PORT);
    printf("Waiting for client data...\n");

    /* Server loop: Receives from client, displays, and echoes back */
    while (1)
    {
        /* 1. Receive structure from client */
        int n = recvfrom(server_socket,
                         (char *)&message,
                         sizeof(message),
                         0,
                         (struct sockaddr *)&client_addr,
                         &client_len);

        if (n < 0)
        {
            perror("Error receiving client message");
            break;
        }

        /* 2. Display the received string */
        printf("\n[RECEIVED] Client says: %s\n", message.data);

        /* 3. Echo/Send the exact structure back to the client */
        sendto(server_socket,
               (char *)&message,
               sizeof(message),
               0,
               (struct sockaddr *)&client_addr,
               client_len);

        printf("[SENT] Echoed back to client.\n");

        /* Exit condition check */
        if (strcmp(message.data, "exit") == 0)
        {
            printf("Exit signal received. Shutting down server.\n");
            break;
        }
    }

    close(server_socket);
    return 0;
}
