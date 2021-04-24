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
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != -1) {
        write(serv->current->client, line, strlen(line));
    }
    free(line);
}

void close_data_socket(server_t *serv)
{
    serv->current->pasv = false;
    serv->current->port = false;
    close(serv->current->data_master);
    close(serv->current->client);
}

char *get_file_name(const char *filepath)
{
    int len = strlen(filepath);
    char *str = malloc(len + 1);
    int pos, i;
    for (pos = len - 1; pos > 0; pos--)
        if (filepath[pos] == '/') {
            pos++;
            break;
        }
    for (i = 0; pos < len; i++, pos++) {
        str[i] = filepath[pos];
    }
    str[i] = '\0';
    return (str);
}