/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** main
*/

#include "my_ftp.h"

void display_usage(void)
{
    write(1, "USAGE: ./myftp port path\n", 25);
    write(1,
    "\tport is the port number on witch the server socket listens\n", 60);
    write(1,
    "\tpath is the path to the home directory for the Anonymous user\n", 63);
    exit(0);
}

void parse_main(int ac, char **av, server_t *serv)
{
    if (ac < 3)
        display_usage();
    struct stat st = {0};
    serv->port = atoi(av[1]);
    if (stat(av[2], &st) == -1)
        exit(84);
    char tmp[PATH_MAX];
    getcwd(tmp, sizeof(tmp));
    chdir(av[2]);
    getcwd(serv->work, sizeof(serv->work));
    chdir(tmp);
}

int main(int ac, char **av)
{
    server_t server = {0};
    signal(SIGPIPE, SIG_IGN);
    parse_main(ac, av, &server);
    server.set_head = NULL;
    init_server(&server);
    start_server(&server);
    return (EXIT_SUCCESS);
}