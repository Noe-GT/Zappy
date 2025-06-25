##
## EPITECH PROJECT, 2025
## zappy
## File description:
## Makefile
##

SERVER_SRC	=	$(wildcard server/*.c)

GUI_SRC 	= 	$(shell find gui/client -type f -name '*.cpp') 		\

RENDERS_SRC = 	$(shell find gui/UI/shared -type f -name '*.cpp') 	\
				$(wildcard gui/*.cpp)								\
				$(shell find gui/game -type f -name '*.cpp') 		\

AI_SRC 		= 	$(wildcard ai/*.c)

SERVER_OBJ 	= 	$(SERVER_SRC:.c=.o)
GUI_OBJ 	= 	$(GUI_SRC:.cpp=.o)
AI_OBJ 		= 	$(AI_SRC:.c=.o)
RENDERS_OBJ = 	$(RENDERS_SRC:.cpp=.plugin.o)

SERVER_EXEC = 	zappy_server
GUI_EXEC 	= 	zappy_gui
AI_EXEC 	= 	zappy_ai

CC 			= 	gcc

CPPC 		= 	g++

CFLAGS 		+= 	-Wall -Wextra -g3

CPPFLAGS 	= 	-std=c++17

GUI_LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -ldl

all: server gui ai

server: $(SERVER_EXEC)

$(SERVER_EXEC): $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) -o $(SERVER_EXEC) $(CFLAGS)

gui: $(RENDERS_OBJ) $(GUI_EXEC)

$(GUI_EXEC): $(GUI_OBJ)
	mkdir -p gui/plugins/
	@for dir in $(shell find gui/UI/render -type f -name Makefile -exec dirname {} \;); do 	\
		$(MAKE) -C $$dir; 																	\
		mv $$dir/*.so gui/plugins/;													 		\
	done
	$(CPPC) $(GUI_OBJ) $(RENDERS_OBJ) -o $(GUI_EXEC) $(CFLAGS) $(CPPFLAGS) $(GUI_LDFLAGS)

ai: $(AI_EXEC)

$(AI_EXEC): $(AI_OBJ)
	$(CC) $(AI_OBJ) -o $(AI_EXEC) $(CFLAGS)

clean:
	@for dir in $(shell find gui/UI/render -type f -name Makefile -exec dirname {} \;); do 	\
		$(MAKE) -C $$dir clean; 															\
	done
	rm -f vgcore.* $(SERVER_OBJ) $(GUI_OBJ) $(AI_OBJ) $(RENDERS_OBJ) $(GUI_SHARED_OBJ) *.gch

fclean: clean
	@for dir in $(shell find gui/UI/render -type f -name Makefile -exec dirname {} \;); do 	\
		$(MAKE) -C $$dir fclean;															\
	done
	rm -rf gui/plugins/
	rm -f $(SERVER_EXEC) $(GUI_EXEC) $(AI_EXEC)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CPPC) $(CFLAGS) $(CPPFLAGS) -fPIC -c $< -o $@

%.plugin.o: %.cpp
	$(CPPC) $(CFLAGS) $(CPPFLAGS) -fPIC -c $< -o $@

%.shared.o: %.cpp
	$(CPPC) $(CFLAGS) $(CPPFLAGS) -fPIC -c $< -o $@

.PHONY: server gui ai clean fclean re