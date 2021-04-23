/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** cmd
*/

#include "my_ftp.h"

static const char *const cmd[CMD_SIZE] =
            {"USER", "PASS", "QUIT", "NOOP",
            "HELP", "PWD", "CWD", "CDUP",
            "PASV", "LIST", "DELE"};

void (*func_cmd[CMD_SIZE])(server_t *) =
            {cmd_user, cmd_pass, cmd_quit, cmd_noop,
            cmd_help, cmd_pwd, cmd_cwd, cmd_cdup,
            cmd_pasv, cmd_list, cmd_dele};

void parse_command(server_t *serv)
{
    char *token;
    token = strtok(serv->buf, " \r\n");
    int itr = 0;
    for (; itr < CMD_SIZE; itr++)
        if (token != NULL && strcmp(cmd[itr], token) == 0) break;
    if (itr != CMD_SIZE)
        func_cmd[itr](serv);
    else
        write_response(serv->current->fd, "500 command unrecognized.\r\n");
    clear_cmd();
}