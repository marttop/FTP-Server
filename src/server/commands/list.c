/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** list
*/

#include "my_ftp.h"

int file_exist(const char *file, server_t *serv)
{
    char tmp[PATH_MAX];
    int fd;
    getcwd(tmp, sizeof(tmp));
    chdir(serv->current->work);
    if ((fd = open(file, O_RDONLY)) != -1) {
        chdir(tmp);
        close(fd);
        return (1);
    }
    chdir(tmp);
    return (0);
}

int list_current_dir(server_t *serv, const char *arg)
{
    FILE *fp;
    char tmp[PATH_MAX], str[PATH_MAX];
    getcwd(tmp, sizeof(tmp));
    chdir(serv->current->work);
    if (arg != NULL) {
        strcpy(str, "ls -l "), strcat(str, arg);
        fp = popen(str, "r");
    } else fp = popen("ls -l", "r");
    chdir(tmp);
    serv->current->child = fork();
    if (serv->current->child == 0) {
        write_data_pasv(serv, fp);
        write_response(serv->current->fd, "226 Closing data connection.\r\n");
        exit(1);
    } else
        write_response(serv->current->fd, "150 File status okay.\r\n");
    return (0);
}

void cmd_list(server_t *serv)
{
    if (serv->current->logged &&
    (serv->current->pasv || serv->current->port)) {
        char *token = strtok(NULL, " \r\n");
        if (token == NULL) {
            list_current_dir(serv, NULL);
        }
        else if (token != NULL && file_exist(token, serv)) {
            list_current_dir(serv, token);
        }
        else write_response(serv->current->fd, "550 No file.\r\n");
    }
    else if (serv->current->logged &&
    !serv->current->pasv && !serv->current->port)
        write_response(serv->current->fd, "425 Enable PASV or PORT.\r\n");
    else write_response(serv->current->fd, "530 Not logged in.\r\n");
}