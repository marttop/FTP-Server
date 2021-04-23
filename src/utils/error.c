/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** error
*/

#include "my_ftp.h"

void handle_error(const char *msg)
{
    perror(msg);
    exit(84);
}