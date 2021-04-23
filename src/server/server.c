/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** server
*/

#include "my_ftp.h"

void add_socket(server_t *serv)
{
    fd_t *tmp = serv->set_head;
    while (tmp != NULL) {
        if (tmp->fd > 0)
            FD_SET(tmp->fd, &serv->set);
        if (tmp->fd > serv->max_sd)
            serv->max_sd = tmp->fd;
        tmp = tmp->next;
    }
}

void connect_client(server_t *serv)
{
    if (FD_ISSET(serv->fdserv, &serv->set)) {
        if ((serv->fdclient = accept(serv->fdserv,
        (struct sockaddr *)&serv->client, &serv->size)) < 0)
            handle_error("accept");
        printf("New connection , socket fd is %d , ip is : %s , port : %d\n",
            serv->fdclient,
            inet_ntoa(serv->client.sin_addr),
            ntohs(serv->client.sin_port));
        write_response(serv->fdclient, "220 Service ready for new user.\r\n");
        puts("Welcome message sent successfully");
        push_back(serv->fdclient, serv);
    }
}

void check_client_disconnection(server_t *serv)
{
    fd_t *tmp = serv->set_head;
    int val = 0;
    pid_t wait;
    while (tmp != NULL) {
        if ((wait = waitpid(tmp->child, 0, WNOHANG)) > 0)
            close_data_socket(serv);
        if (FD_ISSET(tmp->fd, &serv->set)) {
            memset(serv->buf, '\0', sizeof(char) * 99);
            if ((val = read(tmp->fd, serv->buf, 99)) == 0) {
                getpeername(tmp->fd, (struct sockaddr *)&serv->client,
                    (socklen_t *)&serv->size);
                printf("Host disconnected , ip %s , port %d \n",
                    inet_ntoa(serv->client.sin_addr),
                    ntohs(serv->client.sin_port));
                close(tmp->fd), tmp->fd = 0;
            } else
                serv->current = tmp, parse_command(serv);
        }
        tmp = tmp->next;
    }
}

void start_server(server_t *serv)
{
    serv->size = sizeof(serv->client);
    int act;
    FD_ZERO(&serv->set);
    while (1) {
        FD_ZERO(&serv->set);
        FD_SET(serv->fdserv, &serv->set);
        serv->max_sd = serv->fdserv;
        add_socket(serv);
        act = select(serv->max_sd + 1, &serv->set, NULL, NULL, NULL);
        if ((act < 0) && (errno != EINTR))
            handle_error("select");

        connect_client(serv);
        clear_list(serv);
        check_client_disconnection(serv);
    }
    close(serv->fdserv);
}