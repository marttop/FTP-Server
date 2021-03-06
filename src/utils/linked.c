/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marton.szuts
** File description:
** linked
*/

#include "my_ftp.h"

void init_node(fd_t *node)
{
    memset(node, 0, sizeof(fd_t));
    node->next = NULL;
    node->logged = false;
    node->pasv = false;
    node->port = false;
}

void push_back(int fd, server_t *serv)
{
    fd_t *tmp = serv->set_head;
    fd_t *new = malloc(sizeof(fd_t));
    init_node(new);
    new->fd = fd;
    strcpy(new->work, serv->work);
    if (tmp != NULL) {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new;
    }
    else
        serv->set_head = new;
    serv->current = new;
}

void clear_list(server_t *serv)
{
    fd_t *tmp = serv->set_head, *prev = NULL, *free_tmp = NULL;
    if (serv->set_head != NULL && serv->set_head->fd == 0) {
        tmp = tmp->next;
        free(serv->set_head);
        serv->set_head = tmp;
    }
    while (tmp != NULL) {
        if (tmp->next != NULL && tmp->next->fd == 0) prev = tmp;
        if (prev != NULL && tmp->fd == 0) {
            prev->next = tmp->next, free_tmp = tmp;
            tmp = tmp->next;
            free(free_tmp);
            continue;
        } if (tmp->next == NULL && tmp->fd == 0) {
            serv->set_head = NULL, free(tmp);
            break;
        } tmp = tmp->next;
    }
}