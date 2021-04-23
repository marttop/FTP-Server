/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** delete
*/

#include "my_ftp.h"

void cmd_dele(server_t *serv)
{
    char *token = strtok(NULL, " \r\n"), *safe = strtok(NULL, " \r\n");
    if (serv->current->logged) {
        char tmp[PATH_MAX];
        getcwd(tmp, sizeof(tmp));
        chdir(serv->current->work);
        if (token != NULL && safe == NULL && !remove(token)) {
            write_response(serv->current->fd,
            "250 Requested file action okay, completed.\r\n");
        }
        else if (safe != NULL)
            write_response(serv->current->fd, "501 Syntax error.\r\n");
        else
            write_response(serv->current->fd, "550 No such file.\r\n");
    }
    else
        write_response(serv->current->fd, "530 Not logged in.\r\n");
}