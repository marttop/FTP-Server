/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** client
*/

#include "my_ftp.h"

void client_loop(client_t *client)
{
    int n = 0;
    while (1) {
        bzero(client->buf, 100);
        int size_rec = read(client->fdclient, client->buf, 99 * sizeof(char));
        client->buf[size_rec] = '\0';
        if (size_rec) {
            printf("Caracteres recus : %d\n", size_rec);
            printf("Message : %s\n", client->buf);
        }
        bzero(client->buf, 100);
        for (n = 0; (client->buf[n] = getchar()) != '\n'; n++);
        client->buf[n] = '\0';
        write(client->fdclient, client->buf, strlen(client->buf));
    }
}

int main(int ac, char **av)
{
    if (ac < 3) {
        printf("Usage: ./client.so ip port\n");
        return (84);
    }
    client_t client = {0};
    client.size = sizeof(struct sockaddr_in);
    client.client_addr.sin_family = AF_INET;
    client.client_addr.sin_port = htons(atoi(av[2]));
    inet_aton(av[1], &client.client_addr.sin_addr);
    client.fdclient = socket(PF_INET, SOCK_STREAM, 0);
    if (connect(client.fdclient, (struct sockaddr *)&client.client_addr,
    sizeof(struct sockaddr_in)) != -1) {
        bzero(client.buf, 100);
        client_loop(&client);
    } else
        handle_error("connect");
}