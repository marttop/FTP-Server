/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** misc
*/

#include "my_ftp.h"

void cmd_help(server_t *serv)
{
    write(serv->current->fd, "214 GOOGLE FTP HAHAHA.\r\n", 24);
}

void cmd_noop(server_t *serv)
{
    write(serv->current->fd, "200 Command okay.\r\n", 19);
}

void cmd_pwd(server_t *serv)
{
    write(serv->current->fd, "257 ", 4);
    write(serv->current->fd, serv->work, strlen(serv->work));
}