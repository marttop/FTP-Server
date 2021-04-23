/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** data_transfert
*/

#include "my_ftp.h"

int get_free_port(server_t *serv)
{
    int i = 1024;
    for (; i < SHRT_MAX; i++) {
        serv->current->s.sin_port = htons(i);
        if (bind(serv->current->data_master,
        (struct sockaddr *)(&serv->current->s),
        sizeof(serv->current->s)) != -1)
            break;
    }
    if (i == SHRT_MAX)
        return (-1);
    return (i);
}

void pasv_response(server_t *serv, int port)
{
    char buf[100];
    char port_buf[50];
    int res = 0;
    memset(buf, '\0', 100 * sizeof(char));
    strcpy(buf, "227 Entering Passive Mode (127,0,0,1,");
    res = port % 256;
    sprintf(port_buf, "%d,%d).\r\n", (port - port % 256) / 256, res);
    strcat(buf, port_buf);
    write(serv->current->fd, buf, strlen(buf));
}

void cmd_pasv(server_t *serv)
{
    if (serv->current->logged && !serv->current->pasv) {
        int port = 0;
        memset(&serv->current->s, 0, sizeof(serv->current->s));
        serv->current->data_master = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        serv->current->s.sin_family = AF_INET;
        serv->current->s.sin_addr.s_addr = htonl(INADDR_ANY);
        if ((port = get_free_port(serv)) != -1) {
            listen(serv->current->data_master, 40);
            pasv_response(serv, port);
            serv->current->client = accept(serv->current->data_master,
            (struct sockaddr *)&serv->current->s, &serv->size);
            serv->current->pasv = true;
        }
        else {
            write_response(serv->current->fd,
                "434 Requested host unavailable.\r\n");
        }
    }
    else
        write_response(serv->current->fd, "530 Not logged in.\r\n");
}