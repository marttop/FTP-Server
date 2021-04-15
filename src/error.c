/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** error
*/

#include "my_ftp.h"

bool is_loop = true;

void handle_error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void sigint_handler(int signal)
{
    if (signal == SIGINT)
        is_loop = false;
}