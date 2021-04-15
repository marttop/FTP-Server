/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** my_ftp
*/

#ifndef MY_FTP_H_
#define MY_FTP_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <strings.h>

typedef struct server {
    int fdserv;
    int fdclient;
    struct sockaddr_in serv_addr;
    socklen_t size;
    char buf[100];
} server_t;

typedef struct client {
    int fdclient;
    struct sockaddr_in client_addr;
    socklen_t size;
    char buf[100];
} client_t;

void handle_error(const char *msg);
void init_server(server_t *serv);
void start_server(server_t *serv);

#endif /* !MY_FTP_H_ */
