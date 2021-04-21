/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** auth
*/

#include "my_ftp.h"

void user_cmd(server_t *serv)
{
    char *token = strtok(NULL, " \r\n");
    if (serv->current->logged) {
        write(serv->fdclient, "230 User logged in, proceed.\r\n", 30);
        return;
    }
    if (token != NULL && strcmp(token, "Anonymous") == 0) {
        serv->current->username = true;
        write(serv->current->fd, "331 User name okay, need password.\r\n", 36);
    }
    else
        write(serv->current->fd, "430 Invalid username or password.\r\n", 35);
}

void user_pass(server_t *serv)
{
    char *token = strtok(NULL, " \r\n");
    if (serv->current->logged) {
        write(serv->fdclient, "230 User logged in, proceed.\r\n", 30);
        return;
    }
    if (!serv->current->username)
        write(serv->fdclient, "332 Need account for login.\r\n", 29);
    else if ((token == NULL || strcmp(token, "") == 0)
    && serv->current->username) {
        serv->current->logged = true;
        write(serv->fdclient, "230 User logged in, proceed.\r\n", 30);
    }
    else
        write(serv->current->fd, "430 Invalid username or password.\r\n", 35);
}