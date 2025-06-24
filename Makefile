##
## EPITECH PROJECT, 2025
## zappy
## File description:
## Makefile
##

SERVER_SRC		=	$(shell find server -type f -name '*.c')
GUI_SRC			=	$(shell find gui -type f -name '*.cpp')
AI_SRC			=	ai/zappy_ai
PROTOCOL_SRC	=	$(shell find protocol -type f -name '*.c')
TEST_SRC		=	$(shell find tests -type f -name '*.c')

SERVER_OBJ		=	$(SERVER_SRC:.c=.o)
GUI_OBJ			=	$(GUI_SRC:.cpp=.o)
PROTOCOL_OBJ	=	$(PROTOCOL_SRC:.c=.o)
TEST_OBJ		=	$(TEST_SRC:.c=.o)

TEST_SERVER		=	$(filter-out server/src/main.o, $(SERVER_OBJ))

SERVER_EXEC		=	zappy_server
GUI_EXEC		=	zappy_gui
AI_EXEC			=	zappy_ai
PROTOCOL_EXEC	=	libprotocol.so
TEST_EXEC		=	unit_tests

CC				=	gcc

CPPC			=	g++

CPY				= 	nuitka

CFLAGS			+=	-Wall -Wextra -g3 -fPIC -Iprotocol/include -Iserver/include

CRITERION		=	--coverage -lcriterion

all:	$(SERVER_EXEC)	$(GUI_EXEC)	$(AI_EXEC)

tests_run:	$(TEST_OBJ)	$(TEST_SERVER)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_OBJ) $(TEST_SERVER) $(CRITERION)
	./$(TEST_EXEC)

$(PROTOCOL_EXEC): $(PROTOCOL_OBJ)
	$(CC) $(PROTOCOL_OBJ) -o $(PROTOCOL_EXEC) $(CFLAGS) -shared

$(SERVER_EXEC): $(SERVER_OBJ) $(PROTOCOL_EXEC)
	$(CC) $(SERVER_OBJ) $(CFLAGS) -o $(SERVER_EXEC) -L. -lprotocol

$(GUI_EXEC):	$(GUI_OBJ)
	$(CPPC) $(GUI_OBJ) -o $(GUI_EXEC) $(CFLAGS)

$(AI_EXEC): $(AI_SRC)
	$(CPY) --standalone --onefile --output-dir=. --output-filename=$(AI_EXEC) --enable-plugin=tk-inter --follow-imports $(AI_SRC)
clean:
	rm -f $(SERVER_OBJ)
	rm -f $(GUI_OBJ)
	rm -f $(AI_OBJ)
	rm -f $(PROTOCOL_OBJ)
	rm -f $(TEST_OBJ)
	rm -f vgcore.*
	rm -f *.gch
	rm -rf  ai/__pycache__ *.spec *.dist

fclean:	clean
	rm -f $(GUI_EXEC) $(AI_EXEC) $(SERVER_EXEC) $(PROTOCOL_EXEC) $(TEST_EXEC)

re:	fclean	all

.PHONY:	clean 	fclean	re	install
