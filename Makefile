##
## EPITECH PROJECT, 2025
## zappy
## File description:
## Makefile
##

SERVER_DIR	=	server/

SERVER_SRC	=	$(SERVER_DIR)src/main.c	\
				$(SERVER_DIR)src/server.c	\
				$(SERVER_DIR)src/network/network.c	\
				$(SERVER_DIR)src/network/clients.c	\
				$(SERVER_DIR)src/network/queue.c	\
				$(SERVER_DIR)src/network/network_utils.c	\

GUI_SRC	=	$(wildcard gui/*.cpp)
AI_SRC	=	$(wildcard ai/*.c)

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)
GUI_OBJ	=	$(GUI_SRC:.cpp=.o)
AI_OBJ	=	$(AI_SRC:.c=.o)

SERVER_EXEC	=	zappy_server
GUI_EXEC	=	zappy_gui
AI_EXEC		=	zappy_ai

CC	=	gcc

CPPC	=	g++

CFLAGS	+=	-Wall -Wextra -g3

all:	server gui	ai

server: $(SERVER_EXEC)

$(SERVER_EXEC): $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) -o $(SERVER_EXEC) $(CFLAGS)

gui:	$(GUI_EXEC)

$(GUI_EXEC):	$(GUI_OBJ)
	$(CPPC) $(GUI_OBJ) -o $(GUI_EXEC) $(CFLAGS)

ai: $(AI_EXEC)

$(AI_EXEC): $(AI_OBJ)
	$(CC) $(AI_OBJ) -o $(AI_EXEC) $(CFLAGS)

clean:
	rm -f vgcore.* $(SERVER_OBJ) $(GUI_OBJ)
	rm -f $(AI_OBJ) *.gch

fclean:	clean
	rm -f $(SERVER_EXEC) $(GUI_EXEC) $(AI_EXEC)

re:	fclean	all

.PHONY:	server	gui	ai	clean	fclean	re
