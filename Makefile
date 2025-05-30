##
## EPITECH PROJECT, 2025
## zappy
## File description:
## Makefile
##

SERVER_DIR	=	server/

GUI_SRC	=	$(wildcard gui/*.cpp)
AI_SRC	=	$(wildcard ai/*.c)

GUI_OBJ	=	$(GUI_SRC:.cpp=.o)
AI_OBJ	=	$(AI_SRC:.c=.o)

GUI_EXEC	=	zappy_gui
AI_EXEC		=	zappy_ai

CC	=	gcc

CPPC	=	g++

CFLAGS	+=	-Wall -Wextra -g3

all:	server gui	ai

server:
	make -C $(SERVER_DIR)

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
