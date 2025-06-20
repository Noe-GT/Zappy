## EPITECH PROJECT, 2024
## zap
## File description:
## Makefile
##

CXX        = 	g++

CXXFLAGS   = 	-Wall -Wextra -std=c++17 -fPIC -Iinclude

LDFLAGS    = 	-shared
LIBS       = 	-lsfml-graphics -lsfml-window -lsfml-system -lGLEW -lglfw -lOpenGL

NAME       = 	libRender3d.so

SRC        = 	$(shell find src -type f -name '*.cpp')

OBJ        = 	$(SRC:.cpp=.o)											\
				$(shell find ../../../../ -type f -name '*.plugin.o')

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS) -Wl,--no-as-needed

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re