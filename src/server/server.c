/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** server
*/

#include "my_ftp.h"

void init_server(server_t *serv)
{
    memset(&serv->serv_addr, 0, sizeof(serv->serv_addr));
    serv->fdserv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serv->fdserv == -1)
        handle_error("server socket");
    serv->serv_addr.sin_family = AF_INET;
    serv->serv_addr.sin_port = htons(4242);
    serv->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(serv->fdserv, (struct sockaddr*)(&serv->serv_addr), sizeof(serv->serv_addr)) == -1)
        handle_error("bind");
    if (listen(serv->fdserv, 3) == -1)
        handle_error("listen");
}

void start_server(server_t *serv)
{
    struct sockaddr client = {0};
    serv->size = sizeof(client);
    serv->fdclient = accept(serv->fdserv, &client, &serv->size);
    if (serv->fdclient > 0)
        printf("Connection complete\n");
    while (read(serv->fdclient, serv->buf, 100) > 0)
        printf("%s\n", serv->buf);
}