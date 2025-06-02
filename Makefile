##
## EPITECH PROJECT, 2025
## zappy
## File description:
## Makefile
##

SERVER_DIR	=	server/

GUI_SRC	=	$(wildcard gui/*.cpp)
AI_SRC	=	$(wildcard ai/*.c)
PROTOCOL_SRC	=	$(wildcard protocol/src/*.c)

GUI_OBJ	=	$(GUI_SRC:.cpp=.o)
AI_OBJ	=	$(AI_SRC:.c=.o)
PROTOCOL_OBJ	=	$(PROTOCOL_SRC:.c=.o)

GUI_EXEC	=	zappy_gui
AI_EXEC		=	zappy_ai
PROTOCOL_EXEC	=	libprotocol.so

CC	=	gcc

CPPC	=	g++

# TODO: remove debug information
CFLAGS	+=	-Wall -Wextra -g3

all:	server gui	ai	protocol

tests_run:
	make tests_run -C $(SERVER_DIR)

server:
	make -C $(SERVER_DIR)

protocol: $(PROTOCOL_EXEC)

$(PROTOCOL_EXEC): $(PROTOCOL_OBJ)
	$(CC) $(PROTOCOL_OBJ) -o $(PROTOCOL_EXEC) $(CFLAGS) -shared

gui:	$(GUI_EXEC)

$(GUI_EXEC):	$(GUI_OBJ)
	$(CPPC) $(GUI_OBJ) -o $(GUI_EXEC) $(CFLAGS)

ai: $(AI_EXEC)

$(AI_EXEC): $(AI_OBJ)
	$(CC) $(AI_OBJ) -o $(AI_EXEC) $(CFLAGS)

clean:
	rm -f vgcore.* $(GUI_OBJ)
	rm -f $(AI_OBJ) *.gch
	make clean -C $(SERVER_DIR)

fclean:	clean
	rm -f $(GUI_EXEC) $(AI_EXEC)
	make fclean -C $(SERVER_DIR)

re:	fclean	all

.PHONY:	server	gui	ai	clean	fclean	re
