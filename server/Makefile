##
## EPITECH PROJECT, 2025
## zappy
## File description:
## Makefile
##

ROOT_DIR	=	../

SRC_DIR	=	src/

TEST_DIR	=	tests/

SERVER_SRC	=	$(SRC_DIR)server.c	\
				$(SRC_DIR)network/network.c	\
				$(SRC_DIR)network/clients.c	\
				$(SRC_DIR)network/queue.c	\
				$(SRC_DIR)network/network_utils.c	\
				$(SRC_DIR)network/client_list.c	\
				$(SRC_DIR)main.c	\

TEST_SRC	=	$(TEST_DIR)client_list.c	\

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)

TEST_SERVER_OBJ = $(filter-out $(SRC_DIR)main.o, $(SERVER_OBJ))

TEST_OBJS	=	$(TEST_SRC:.c=.o)

CRITERION	=	--coverage -lcriterion

TEST_NAME	=	unit_tests

SERVER_EXEC	=	$(ROOT_DIR)zappy_server

CC	=	gcc

CFLAGS	+=	-Wall -Wextra -g3

all:	$(SERVER_EXEC)

$(SERVER_EXEC): $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) -o $(SERVER_EXEC) $(CFLAGS)

tests_run:	all
	$(CC) $(CFLAGS) -o $(TEST_NAME) $(TEST_SRC) $(TEST_SERVER_OBJ) $(CRITERION)
	./$(TEST_NAME)

clean:
	rm -f vgcore.* $(SERVER_OBJ) $(GUI_OBJ)
	rm -f $(AI_OBJ) *.gch
	rm -f *gcno
	rm -f *gcda

fclean:	clean
	rm -f $(SERVER_EXEC) $(GUI_EXEC) $(AI_EXEC)
	rm -f $(TEST_NAME)

re:	fclean	all

.PHONY:	server	gui	ai	clean	fclean	re tests_run
