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

UNAME_S	:=	$(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	LDFLAGS +=		-undefined dynamic_lookup
else
	OBJ	+=			$(shell find ../../../../gui/UI/shared -type f -name '.plugin.o')	\
					$(shell find ../../../../gui/game -type f -name '.plugin.o')		\
					$(shell find ../../../../gui -maxdepth 1 -type f -name '.plugin.o')	\
					$(shell find ../../../../gui/client -type f -name '.o')
endif

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
