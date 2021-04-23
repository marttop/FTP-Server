/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** init
*/

#include "my_ftp.h"

void init_server(server_t *serv)
{
    memset(&serv->serv_addr, 0, sizeof(serv->serv_addr));
    serv->fdserv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serv->fdserv == -1)
        handle_error("server socket");
    serv->serv_addr.sin_family = AF_INET;
    serv->serv_addr.sin_port = htons(serv->port);
    serv->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(serv->fdserv, (struct sockaddr *)(&serv->serv_addr),
    sizeof(serv->serv_addr)) == -1)
        handle_error("bind");
    if (listen(serv->fdserv, 40) == -1)
        handle_error("listen");
}