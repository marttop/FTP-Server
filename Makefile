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

CALL_MAKE_CLIENT	=	cd src/client && make && mv client.out ../../

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -g3 -O0 -I./include

all:	$(NAME)

client:
		$(CALL_MAKE_CLIENT)

$(NAME):	$(OBJS) $(SRCS)
		$(CALL_MAKE_CLIENT)
		gcc -o $(NAME) $(OBJS)

clean:
		rm -rf $(OBJS)
		cd src/client && make clean

fclean:
		rm -rf $(OBJS)
		rm -rf $(NAME)
		cd src/client && make fclean

re: fclean all

.PHONY: all clean fclean re