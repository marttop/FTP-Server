/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** cmd
*/

#include "my_ftp.h"

static const char *const cmd[] = {"USER", "PASS"};

void (*func_cmd[])(server_t *) = {user_cmd, user_pass};

void parse_command(server_t *serv)
{
    char *token;
    token = strtok(serv->buf, " \r\n");
    int itr = 0;
    for (; itr < CMD_END; itr++)
        if (token != NULL && strcmp(cmd[itr], token) == 0) break;
    if (itr != CMD_END)
        func_cmd[itr](serv);
    else
        write(serv->current->fd, "500 command unrecognized.\r\n", 27);
}