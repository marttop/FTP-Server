/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** client
*/

#include "my_ftp.h"

void enable_pasv(client_t *client)
{
    for (int i = 0; i < 7; i++)
        strtok(NULL, " \r\n(),");
    client->d_t.sin_family = AF_INET;
    int a = atoi(strtok(NULL, " \r\n(),"));
    int b = atoi(strtok(NULL, " \r\n(),"));
    client->d_t.sin_port = htons(a * 256 + b);
    inet_aton("127.0.0.1", &client->d_t.sin_addr);
    client->data = socket(PF_INET, SOCK_STREAM, 0);
    if (connect(client->data, (struct sockaddr *)&client->d_t,
    sizeof(struct sockaddr_in)) == -1) {
        handle_error("connect");
    }
}

int parse_code(client_t *client)
{
    char *token = strtok(client->buf, " \r\n(),");
    if (token != NULL && strcmp(token, "221") == 0) return (1);
    if (token != NULL && strcmp(token, "227") == 0) enable_pasv(client);
    clear_cmd();
    return (0);
}

void data_transfert(client_t *client)
{
    int ready, size_rec = 0;
    if (client->data != 0) {
        client->set.fd = client->data;
        ready = poll(&client->set, 1, 0);
        memset(client->buf, '\0', 100 * sizeof(char));
        if (ready > 0) {
            size_rec = read(client->data, client->buf, 99 * sizeof(char));
            client->buf[size_rec] = '\0';
            printf("%s", client->buf);
        }
    }
}

int check_buffer(client_t *client)
{
    char buf[255];
    strcpy(buf, client->buf);
    char *token = strtok(buf, " \r\n,.()");
    if (token != NULL && strcmp(token, "PORT") == 0) {
        int i = 1;
        memset(&client->d_t, 0, sizeof(client->d_t));
        client->port_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        setsockopt(client->port_client,
        SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int));
        client->d_t.sin_family = AF_INET;
        client->d_t.sin_addr.s_addr = htonl(INADDR_ANY);
        for (int i = 0; i < 4; i++)
            strtok(NULL, " \r\n(),");
        int a = atoi(strtok(NULL, " \r\n(),"));
        int b = atoi(strtok(NULL, " \r\n(),"));
        client->d_t.sin_port = htons(a * 256 + b);
        if (bind(client->port_client,
        (struct sockaddr *)(&client->d_t),
        sizeof(client->d_t)) != -1) {
            listen(client->port_client, 40);
            write(client->fdclient, client->buf, strlen(client->buf));
            client->data = accept(client->port_client,
            (struct sockaddr *)&client->d_t, &client->size);
            return (0);
        } else {
            handle_error("bind");
        }
    }
    return (1);
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
            client->buf[size_rec] = '\0', printf("\n");
            printf("Caracteres recus : %d\n", size_rec);
            printf("Message : %s\n", client->buf);
        } if (ready > 0 && parse_code(client)) break;
        data_transfert(client);
        client->set.fd = 1, ready = poll(&client->set, 1, 0);
        memset(client->buf, '\0', 100 * sizeof(char));
        if (ready > 0) {
            size_rec = read(1, client->buf, 99 * sizeof(char));
            client->buf[size_rec] = '\0';
        } if (check_buffer(client))
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