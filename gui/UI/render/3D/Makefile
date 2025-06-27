##
## EPITECH PROJECT, 2024
## zap
## File description:
## Makefile
##

CXX  		= 		g++

CXXFLAGS 	= 		-Wall -Wextra -std=c++17 -fPIC

LDFLAGS 	= 		-shared -lsfml-graphics -lsfml-window -lsfml-system -L../../../../ -lprotocol

NAME 		= 		libRender3d.so

ROOT_DIR	=	../../../../

SRC 		= 		$(shell find src -type f -name '*.cpp')				\

OBJ 		= 		$(SRC:.cpp=.o)										\
					$(shell find ../../../../gui/UI/shared -type f -name '*.plugin.o') \
					$(shell find ../../../../gui/game -type f -name '*.plugin.o') \
					$(shell find ../../../../gui -maxdepth 1 -type f -name '*.plugin.o') \
					$(shell find ../../../../gui/client -type f -name '*.o')

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
