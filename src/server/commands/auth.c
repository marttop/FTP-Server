/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** auth
*/

#include "my_ftp.h"

void cmd_user(server_t *serv)
{
    char *token = strtok(NULL, " \r\n");
    if (serv->current->logged) {
        write_response(serv->current->fd,
        "530 Can't change from guest user.\r\n");
        return;
    }
    if (token != NULL) {
        serv->current->username = true;
        memset(serv->current->user, '\0', sizeof(char) * 255);
        strcpy(serv->current->user, token);
        write_response(serv->current->fd,
        "331 User name okay, need password.\r\n");
    }
    else
        write_response(serv->current->fd,
        "530 USER can't be empty.\r\n");
}

void cmd_pass(server_t *serv)
{
    if (serv->current->logged) {
        write_response(serv->current->fd, "230 User logged.\r\n");
        return;
    }
    if (!serv->current->username) {
        write_response(serv->current->fd, "503 Need USER for login.\r\n");
        return;
    }
    else if (serv->current->username &&
    strcmp(serv->current->user, "Anonymous") == 0) {
        serv->current->logged = true;
        write_response(serv->current->fd, "230 User logged in, proceed.\r\n");
    }
    else {
        write_response(serv->current->fd,
        "430 Invalid username or password.\r\n");
        serv->current->username = false;
    }
}

void cmd_quit(server_t *serv)
{
    serv->current->username = false;
    serv->current->logged = false;
    write_response(serv->current->fd,
    "221 Service closing control connection.\r\n");
    serv->current->fd = 0;
}