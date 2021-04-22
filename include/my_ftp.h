/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** my_ftp
*/

#ifndef MY_FTP_H_
#define MY_FTP_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/select.h>

#define CMD_SIZE 5

typedef struct server {
    int fdserv;
    int fdclient;
    int max_sd;
    int port;
    struct sockaddr_in serv_addr;
    struct sockaddr_in client;
    fd_set set;
    socklen_t size;
    char *path;
    struct fd *set_head;
    struct fd *current;
    char work[255];
    char buf[100];
} server_t;

typedef struct fd {
    int fd;
    bool logged;
    bool username;
    struct fd *next;
} fd_t;

typedef struct client {
    int fdclient;
    struct sockaddr_in client_addr;
    socklen_t size;
    char buf[100];
} client_t;

//Ftp server functions
void handle_error(const char *msg);
void init_server(server_t *serv);
void start_server(server_t *serv);
void sigint_handler(int signal);
void push_back(int fd, server_t *serv);
void clear_list(server_t *serv);
void parse_command(server_t *serv);

//User commands
void cmd_user(server_t *serv);
void cmd_pass(server_t *serv);
void cmd_quit(server_t *serv);
void cmd_help(server_t *serv);
void cmd_noop(server_t *serv);
#endif /* !MY_FTP_H_ */
