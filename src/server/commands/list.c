/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** list
*/

#include "my_ftp.h"

void write_data(server_t *serv, FILE *fp)
{
    while (fgets(serv->buf, 100, fp) != NULL) {
        write(serv->current->client, serv->buf, strlen(serv->buf));
    }
}

int list_current_dir(server_t *serv, const char *arg)
{
    FILE *fp;
    char tmp[PATH_MAX];
    getcwd(tmp, sizeof(tmp));
    chdir(serv->current->work);
    if (arg != NULL)
        fp = popen("ls -l", "r");
    else
        fp = popen("ls -l", "r");
    chdir(tmp);
    pid_t child = fork();
    if (child == 0) {
        write_data(serv, fp);
        write_response(serv->current->fd, "226 Closing data connection.\r\n");
        exit(0);
    }
    else
        write_response(serv->current->fd, "150 File status okay.\r\n");
    return (0);
}

void cmd_list(server_t *serv)
{
    if (serv->current->logged &&
    (serv->current->pasv || serv->current->port)) {
        char *token = strtok(NULL, " \r\n");
        if (token == NULL)
            list_current_dir(serv, NULL);
    }
    else write_response(serv->current->fd, "530 Not logged in.\r\n");
}