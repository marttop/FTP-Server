/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** main
*/

#include "my_ftp.h"

int main(int ac, char **av)
{
    server_t server = {0};
    init_server(&server);
    start_server(&server);
    return (EXIT_SUCCESS);
}