##
## EPITECH PROJECT, 2025
## zappy
## File description:
## Makefile
##

ROOT_DIR	=	../

SRC_DIR	=	src/

SERVER_SRC	=	$(SRC_DIR)main.c	\
				$(SRC_DIR)server.c	\
				$(SRC_DIR)network/network.c	\
				$(SRC_DIR)network/clients.c	\
				$(SRC_DIR)network/queue.c	\
				$(SRC_DIR)network/network_utils.c	\

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)

SERVER_EXEC	=	$(ROOT_DIR)zappy_server

CC	=	gcc

CPPC	=	g++

CFLAGS	+=	-Wall -Wextra -g3

all:	$(SERVER_EXEC)

$(SERVER_EXEC): $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) -o $(SERVER_EXEC) $(CFLAGS)

clean:
	rm -f vgcore.* $(SERVER_OBJ) $(GUI_OBJ)
	rm -f $(AI_OBJ) *.gch

fclean:	clean
	rm -f $(SERVER_EXEC) $(GUI_EXEC) $(AI_EXEC)

re:	fclean	all

.PHONY:	server	gui	ai	clean	fclean	re
