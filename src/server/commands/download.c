/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** download
*/

#include "my_ftp.h"

int copy_file(server_t *serv, const char *arg)
{
    FILE *fp;
    char tmp[PATH_MAX];
    getcwd(tmp, sizeof(tmp));
    chdir(serv->current->work);
    if ((fp = fopen(arg, "r")) != NULL) {
        serv->current->child = fork();
        if (serv->current->child == 0) {
            write_data_pasv(serv, fp);
            write_response(serv->current->fd,
            "226 Closing data connection.\r\n");
            exit(1);
        } else
            write_response(serv->current->fd, "150 File status okay.\r\n");
    } else {
        chdir(tmp);
        return (-1);
    }
    fclose(fp), chdir(tmp);
    return (0);
}

void cmd_retr(server_t *serv)
{
    char *token = strtok(NULL, " \r\n");
    if (serv->current->logged &&
    (serv->current->pasv || serv->current->port)) {
        if (token != NULL && copy_file(serv, token) != -1)
            return;
        else
            write_response(serv->current->fd, "550 No sutch file.\r\n");
    }
    else if (serv->current->logged &&
    !serv->current->pasv && !serv->current->port)
        write_response(serv->current->fd, "425 Enable PASV or PORT.\r\n");
    else
        write_response(serv->current->fd, "530 Not logged in.\r\n");
}