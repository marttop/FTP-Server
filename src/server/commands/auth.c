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
        write_response(serv->current->fd, "230 User logged in, proceed.");
        return;
    }
    if (token != NULL && strcmp(token, "Anonymous") == 0) {
        serv->current->username = true;
        write_response(serv->current->fd, "331 User name okay, need password.");
    }
    else
        write_response(serv->current->fd, "430 Invalid username or password.");
}

void cmd_pass(server_t *serv)
{
    char *token = strtok(NULL, " \r\n");
    if (serv->current->logged) {
        write_response(serv->current->fd, "230 User logged in, proceed.");
        return;
    }
    if (!serv->current->username)
        write_response(serv->current->fd, "332 Need account for login.");
    else if ((token == NULL || strcmp(token, "") == 0)
    && serv->current->username) {
        serv->current->logged = true;
        write_response(serv->current->fd, "230 User logged in, proceed.");
    }
    else
        write_response(serv->current->fd, "430 Invalid username or password.");
}

void cmd_quit(server_t *serv)
{
    if (serv->current->logged) {
        serv->current->username = false;
        serv->current->logged = false;
        write_response(serv->current->fd,
        "221 Service closing control connection.");
        serv->current->fd = 0;
    }
    else
        write_response(serv->current->fd, "530 Not logged in.");
}