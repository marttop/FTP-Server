/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** misc
*/

#include "my_ftp.h"

void cmd_help(server_t *serv)
{
    if (serv->current->logged)
        write_response(serv->current->fd, "214 GOOGLE FTP HAHAHA.\r\n");
    else
        write_response(serv->current->fd, "530 Not logged in.\r\n");
}

void cmd_noop(server_t *serv)
{
    if (serv->current->logged)
        write_response(serv->current->fd, "200 Command okay.\r\n");
    else
        write_response(serv->current->fd, "530 Not logged in.\r\n");
}

void cmd_pwd(server_t *serv)
{
    if (serv->current->logged) {
        char tmp[PATH_MAX];
        memset(tmp, '\0', PATH_MAX * sizeof(char));
        strcat(tmp, "257 ");
        strcat(tmp, serv->current->work);
        strcat(tmp, "\r\n");
        write_response(serv->current->fd, tmp);
    }
    else
        write_response(serv->current->fd, "530 Not logged in.\r\n");
}

void cmd_cwd(server_t *serv)
{
    char *token = strtok(NULL, " \r\n"), *safe = strtok(NULL, " \r\n");
    if (token == NULL) {
        write_response(serv->current->fd, "550 Syntax error.\r\n");
        return;
    } if (serv->current->logged && token != NULL && safe == NULL) {
        char tmp[PATH_MAX];
        getcwd(tmp, sizeof(tmp)), chdir(serv->current->work);
        if (chdir(token) != -1) {
            memset(serv->current->work, '\0', sizeof(char) * PATH_MAX);
            getcwd(serv->current->work, sizeof(serv->current->work));
            write_response(serv->current->fd,
            "250 Requested file action okay, completed.\r\n");
        }
        else
            write_response(serv->current->fd, "550 No such directory.\r\n");
        chdir(tmp);
    }
    else if (safe != NULL)
        write_response(serv->current->fd, "550 Syntax error.\r\n");
    else write_response(serv->current->fd, "530 Not logged in.\r\n");
}

void cmd_cdup(server_t *serv)
{
    if (serv->current->logged) {
        char tmp[PATH_MAX];
        getcwd(tmp, sizeof(tmp));
        chdir(serv->current->work);
        chdir("../");
        memset(serv->current->work, '\0', PATH_MAX * sizeof(char));
        getcwd(serv->current->work, sizeof(serv->current->work));
        chdir(tmp);
        write_response(serv->current->fd, "250 Command okay.\r\n");
    }
    else
        write_response(serv->current->fd, "530 Not logged in.\r\n");
}