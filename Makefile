##
## EPITECH PROJECT, 2025
## zappy
## File description:
## Makefile
##

SERVER_SRC		=	$(shell find server -type f -name '*.c')
# GUI_SRC			=	$(shell find gui -type f -name '*.cpp')
AI_SRC			=	$(shell find ai -type f -name '*.c')
PROTOCOL_SRC	=	$(shell find protocol -type f -name '*.c')
TEST_SRC		=	$(shell find tests -type f -name '*.c')
GUI_SRC 	= 	$(wildcard gui/*.cpp) 								\
				$(shell find gui/client -type f -name '*.cpp') 		\
				$(shell find gui/game -type f -name '*.cpp') 		\

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)
GUI_OBJ	=	$(GUI_SRC:.cpp=.o)
AI_OBJ	=	$(AI_SRC:.c=.o)
PROTOCOL_OBJ	=	$(PROTOCOL_SRC:.c=.o)
TEST_OBJ		=	$(TEST_SRC:.c=.o)

RENDERS_SRC = 	$(shell find gui/UI/shared -type f -name '*.cpp') \
				# $(shell find gui/shared -type f -name '*.cpp')
GUI_SHARED_SRC = 	$(shell find gui/shared -type f -name '*.cpp') \

TEST_SERVER		=	$(filter-out server/src/main.o, $(SERVER_OBJ))

SERVER_EXEC		=	zappy_server
GUI_EXEC		=	zappy_gui
AI_EXEC			=	zappy_ai
PROTOCOL_EXEC	=	libprotocol.so
TEST_EXEC		=	unit_tests

GUI_SHARED_OBJ = 	$(GUI_SHARED_SRC:.cpp=.shared.o)
RENDERS_OBJ = 	$(RENDERS_SRC:.cpp=.plugin.o)

CFLAGS	+=	-Wall -Wextra -g3

CFLAGS	+=	-Wall -Wextra -g3 -fPIC -Iprotocol/include -Iserver/include

CC 			= 	gcc

CPPC 		= 	g++

CPPFLAGS 	= 	-std=c++17

GUI_LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -ldl

CRITERION	=	--coverage -lcriterion

all:	$(SERVER_EXEC)	$(GUI_EXEC)	$(AI_EXEC)

$(PROTOCOL_EXEC): $(PROTOCOL_OBJ)
	$(CC) $(PROTOCOL_OBJ) -o $(PROTOCOL_EXEC) $(CFLAGS) -shared

$(GUI_EXEC): $(GUI_SHARED_OBJ) $(RENDERS_OBJ) $(GUI_OBJ)
	mkdir -p gui/plugins
	@for dir in $(shell find gui/UI/render -type f -name Makefile -exec dirname {} \;); do 	\
		$(MAKE) -C $$dir; 																	\
		cp $$dir/*.so gui/plugins/;													 		\
	done
	$(CPPC) $(GUI_OBJ) $(GUI_SHARED_OBJ) $(RENDERS_OBJ) -o $(GUI_EXEC) $(CFLAGS) $(CPPFLAGS) $(GUI_LDFLAGS)

tests_run:	$(PROTOCOL_EXEC) $(TEST_OBJ)	$(TEST_SERVER)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_OBJ) $(TEST_SERVER) $(CRITERION) \
		-L. -lprotocol
	./$(TEST_EXEC)

$(SERVER_EXEC): $(SERVER_OBJ) $(PROTOCOL_EXEC)
	$(CC) $(SERVER_OBJ) $(CFLAGS) -o $(SERVER_EXEC) -L. -lprotocol

$(AI_EXEC): $(AI_OBJ)
	$(CC) $(AI_OBJ) -o $(AI_EXEC) $(CFLAGS)

clean:
	@for dir in $(shell find gui/UI/render -type f -name Makefile -exec dirname {} \;); do 	\
		$(MAKE) -C $$dir clean; 															\
	done
	rm -f $(SERVER_OBJ)
	rm -f $(GUI_OBJ)
	rm -f $(AI_OBJ)
	rm -f $(PROTOCOL_OBJ)
	rm -f $(TEST_OBJ)
	rm -f $(RENDERS_OBJ)
	rm -f $(GUI_SHARED_OBJ)
	rm -f vgcore.*
	rm -f *.gch

fclean: clean
	@for dir in $(shell find gui/UI/render -type f -name Makefile -exec dirname {} \;); do 	\
		$(MAKE) -C $$dir fclean;															\
	done
	rm -f gui/plugins/*
	rm -f $(GUI_EXEC) $(AI_EXEC) $(SERVER_EXEC) $(PROTOCOL_EXEC) $(TEST_EXEC)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CPPC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

%.plugin.o: %.cpp
	$(CPPC) $(CFLAGS) $(CPPFLAGS) -fPIC -c $< -o $@

%.shared.o: %.cpp
	$(CPPC) $(CFLAGS) $(CPPFLAGS) -fPIC -c $< -o $@

.PHONY:	server	gui	ai	clean	fclean	re
