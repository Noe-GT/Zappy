##
## EPITECH PROJECT, 2024
## zap
## File description:
## Makefile
##

CXX  		= 		g++

CXXFLAGS 	= 		-Wall -Wextra -std=c++17 -fPIC

LDFLAGS 	= 		-shared

NAME 		= 		libRender3d.so

SRC 		= 		$(shell find src -type f -name '*.cpp')

OBJ 		= 		$(SRC:.cpp=.o)											\
					$(shell find ../../shared -type f -name '*.plugin.o')

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re