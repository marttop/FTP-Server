##
## EPITECH PROJECT, 2021
## B-NWP-400-NCE-4-1-myftp-marton.szuts
## File description:
## Makefile
##

NAME	=	myftp

SRCS	=	src/main.c \
			src/error.c \
			src/server/server.c \

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -g3 -O0 -I./include

all:	$(NAME)

$(NAME):	$(OBJS) $(SRCS)
		gcc -o $(NAME) $(OBJS)

clean:
		rm -rf $(OBJS)

fclean:
		rm -rf $(OBJS)
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re