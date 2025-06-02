##
## EPITECH PROJECT, 2025
## zappy
## File description:
## Makefile
##

SERVER_SRC	=	$(wildcard server/*.c)

GUI_SRC		=	$(wildcard gui/*.cpp)														\
				$(wildcard gui/UI/*.cpp)													\
				$(wildcard gui/UI/shared/*.cpp)												\
				$(wildcard gui/client/*.cpp)												\
				$(wildcard gui/client/commands/game/*.cpp)									\
				$(wildcard gui/client/commands/map/*.cpp)									\
				$(wildcard gui/client/commands/misc/*.cpp)									\
				$(wildcard gui/client/commands/player/*.cpp)								\
				$(wildcard gui/client/commands/ressources/*.cpp)							\
				$(wildcard gui/client/commands/settings/*.cpp)								\
				$(wildcard gui/game/*.cpp)													\
				$(wildcard gui/game/Spell*.cpp)												\
				$(wildcard gui/UI/shared/UIBlocks/PopupSelector/*.cpp)						\
				$(wildcard gui/UI/shared/UIBlocks/utils/Scroller/*.cpp)						\

AI_SRC		=	$(wildcard ai/*.c)


SERVER_OBJ	=	$(SERVER_SRC:.c=.o)
GUI_OBJ		=	$(GUI_SRC:.cpp=.o)
AI_OBJ		=	$(AI_SRC:.c=.o)


SERVER_EXEC	=	zappy_server
GUI_EXEC	=	zappy_gui
AI_EXEC		=	zappy_ai

CC			=	gcc

CPPC		=	g++

CFLAGS		+=	-Wall -Wextra -g3

GUI_LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all:	server gui ai

server: $(SERVER_EXEC)

$(SERVER_EXEC): $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) -o $(SERVER_EXEC) $(CFLAGS)

gui:	$(GUI_EXEC)

$(GUI_EXEC):	$(GUI_OBJ)
	$(CPPC) $(GUI_OBJ) -o $(GUI_EXEC) $(CFLAGS) $(GUI_LDFLAGS)

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
