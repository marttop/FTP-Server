/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** port
*/

#include "my_ftp.h"

void fill_infos(server_t *serv)
{
    int id = 1;
    serv->current->s.sin_family = AF_INET;
    serv->current->data_master = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    serv->current->client = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serv->current->data_master,
    SOL_SOCKET, SO_REUSEADDR, &id, sizeof(int));
    serv->current->s.sin_addr.s_addr = htonl(INADDR_ANY);
}

void link_ports(server_t *serv)
{
    char *token = NULL;
    for (int i = 0; i < 4; i++)
        token = strtok(NULL, " \r\n(),");
    if (token != NULL) {
        int a = atoi(strtok(NULL, " \r\n(),"));
        int b = atoi(strtok(NULL, " \r\n(),"));
        serv->current->s.sin_port = htons(a * 256 + b);
        fill_infos(serv);
        if (connect(serv->current->client,
        (struct sockaddr *)&serv->current->s,
        sizeof(struct sockaddr_in)) == -1) {
            close_data_socket(serv);
            write_response(serv->current->fd, "421 Port taken.\r\n");
            return;
        }
        serv->current->port = true;
        write_response(serv->current->fd, "200 Command okay.\r\n");
    } else write_response(serv->current->fd, "421 Service not available.\r\n");
}

void cmd_port(server_t *serv)
{
    if (serv->current->logged && serv->current->port)
        close_data_socket(serv);
    if (serv->current->logged && !serv->current->port) {
        link_ports(serv);
    }
    else
        write_response(serv->current->fd, "530 Not logged in.\r\n");
}