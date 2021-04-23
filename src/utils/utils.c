/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** utils
*/

#include "my_ftp.h"

void write_response(int fd, const char *msg)
{
    if (msg != NULL)
        write(fd, msg, strlen(msg));
}

void clear_cmd(void)
{
    char *token = strtok(NULL, " \r\n");
    while (token != NULL) token = strtok(NULL, " \r\n");
}

void write_data_pasv(server_t *serv, FILE *fp)
{
    while (fgets(serv->buf, 100, fp) != NULL) {
        write(serv->current->client, serv->buf, strlen(serv->buf));
    }
}