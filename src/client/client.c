/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** client
*/

#include "my_ftp.h"

int parse_code(client_t *client)
{
    char *token = strtok(client->buf, " \r\n");
    if (token != NULL && strcmp(token, "221") == 0) return (1);
    clear_cmd();
    return (0);
}

void client_loop(client_t *client)
{
    int ready, size_rec = 0;
    while (1) {
        client->set.fd = client->fdclient;
        ready = poll(&client->set, 1, 0);
        memset(client->buf, '\0', 100 * sizeof(char));
        if (ready > 0) {
            size_rec = read(client->fdclient, client->buf, 99 * sizeof(char));
            client->buf[size_rec] = '\0';
            printf("Caracteres recus : %d\n", size_rec);
            printf("Message : %s\n", client->buf);
        } if (ready > 0 && parse_code(client)) break;
        client->set.fd = 1, ready = poll(&client->set, 1, 0);
        memset(client->buf, '\0', 100 * sizeof(char));
        if (ready > 0) {
            size_rec = read(1, client->buf, 99 * sizeof(char));
            client->buf[size_rec] = '\0';
        }
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
    client.set.fd = 1;
    client.set.events = POLLIN;
    client.size = sizeof(struct sockaddr_in);
    client.client_addr.sin_family = AF_INET;
    client.client_addr.sin_port = htons(atoi(av[2]));
    inet_aton(av[1], &client.client_addr.sin_addr);
    client.fdclient = socket(PF_INET, SOCK_STREAM, 0);
    if (connect(client.fdclient, (struct sockaddr *)&client.client_addr,
    sizeof(struct sockaddr_in)) != -1) {
        client_loop(&client);
    } else
        handle_error("connect");
}