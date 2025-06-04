##
## EPITECH PROJECT, 2025
## zappy
## File description:
## Makefile
##

SERVER_DIR	=	server/

SERVER_SRC	=	$(shell find server -type f -name '*.c')
GUI_SRC	=	$(shell find gui -type f -name '*.cpp')
AI_SRC	=	$(shell find ai -type f -name '*.c')
PROTOCOL_SRC	=	$(shell find protocol -type f -name '*.c')
TEST_SRC	=	$(shell find tests -type f -name '*.c')

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)
GUI_OBJ	=	$(GUI_SRC:.cpp=.o)
AI_OBJ	=	$(AI_SRC:.c=.o)
PROTOCOL_OBJ	=	$(PROTOCOL_SRC:.c=.o)
TEST_OBJ	=	$(TEST_SRC:.c=.o)

TEST_SERVER	=	$(filter-out server/src/main.o, $(SERVER_OBJ))

SERVER_EXEC	=	zappy_server
GUI_EXEC	=	zappy_gui
AI_EXEC		=	zappy_ai
PROTOCOL_EXEC	=	libprotocol.so
TEST_EXEC	=	unit_tests

CC	=	gcc

CPPC	=	g++

# TODO: remove debug information
CFLAGS	+=	-Wall -Wextra -g3 -fPIC -Iprotocol/include
CRITERION	=	--coverage -lcriterion

all:	$(PROTOCOL_EXEC) $(SERVER_EXEC)	$(GUI_EXEC)	$(AI_EXEC)

tests_run:	$(TEST_OBJ)	$(TEST_SERVER)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_OBJ) $(TEST_SERVER) $(CRITERION)

$(PROTOCOL_EXEC): $(PROTOCOL_OBJ)
	$(CC) $(PROTOCOL_OBJ) -o $(PROTOCOL_EXEC) $(CFLAGS) -shared

$(SERVER_EXEC): $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) -o $(SERVER_EXEC) $(CFLAGS) -L. -lprotocol -Wl,-rpath=.

$(GUI_EXEC):	$(GUI_OBJ)
	$(CPPC) $(GUI_OBJ) -o $(GUI_EXEC) $(CFLAGS)

$(AI_EXEC): $(AI_OBJ)
	$(CC) $(AI_OBJ) -o $(AI_EXEC) $(CFLAGS)

clean:
	rm -f $(SERVER_OBJ)
	rm -f $(GUI_OBJ)
	rm -f $(AI_OBJ)
	rm -f $(PROTOCOL_OBJ)
	rm -f $(TEST_OBJ)
	rm -f vgcore.*
	rm -f *.gch

fclean:	clean
	rm -f $(GUI_EXEC) $(AI_EXEC) $(SERVER_EXEC) $(PROTOCOL_EXEC) $(TEST_EXEC)

re:	fclean	all

.PHONY:	clean	fclean	re
