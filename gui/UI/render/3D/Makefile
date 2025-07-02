##
## EPITECH PROJECT, 2024
## zap
## File description:
## Makefile
##

CXX  		= 		g++

CXXFLAGS 	= 		-Wall -Wextra -std=c++17 -fPIC -I../../../ -I../../../../

LDFLAGS 	= 		-shared -lsfml-graphics -lsfml-window -lsfml-system \
					-L../../../../ -lprotocol

NAME 		= 		libRender3d.so

ROOT_DIR	=	../../../../

SRC 		= 		$(shell find src -type f -name '*.cpp')				\

OBJ 		= 		$(SRC:.cpp=.o)

OBJS_LINK = 	$(OBJ) \
	$(ROOT_DIR)/gui/GUI.plugin.o \
	$(ROOT_DIR)/gui/UI/shared/AGraphical.plugin.o \
	$(ROOT_DIR)/gui/UI/shared/Window.plugin.o \
	$(ROOT_DIR)/gui/Tile.plugin.o \
	$(ROOT_DIR)/gui/game/Game.plugin.o \
	$(ROOT_DIR)/gui/game/Player.plugin.o \
	$(ROOT_DIR)/gui/game/spell/Spell.plugin.o \
	$(ROOT_DIR)/gui/game/ressources/*.plugin.o \
	$(ROOT_DIR)/gui/UI/shared/UIBlocks/AUIBlock.plugin.o \
	$(ROOT_DIR)/gui/UI/shared/UIBlocks/Text/Text.plugin.o \
	$(ROOT_DIR)/gui/UI/shared/UIBlocks/Popup/Popup.plugin.o \
	$(ROOT_DIR)/gui/UI/shared/UIBlocks/Timer/Timer.plugin.o \
	$(ROOT_DIR)/gui/UI/shared/UIBlocks/List/List.plugin.o \
	$(ROOT_DIR)/gui/UI/shared/UIBlocks/PopupSelector/PopupSelector.plugin.o \
	$(ROOT_DIR)/gui/UI/shared/UIBlocks/Pair/Pair.plugin.o \
	$(ROOT_DIR)/gui/UI/shared/UIBlocks/Image/Image.plugin.o \
	$(ROOT_DIR)/gui/UI/shared/UIBlocks/utils/Scroller/Scroller.plugin.o \
	$(ROOT_DIR)/gui/client/Client.o \
	$(ROOT_DIR)/gui/client/Cserver.o \
	$(ROOT_DIR)/gui/client/commands/misc/Sbp.o \
	$(ROOT_DIR)/gui/client/commands/misc/WELCOME.o \
	$(ROOT_DIR)/gui/client/commands/misc/Suc.o \
	$(ROOT_DIR)/gui/client/commands/settings/Sgt.o \
	$(ROOT_DIR)/gui/client/commands/settings/Sst.o \
	$(ROOT_DIR)/gui/client/commands/game/Tna.o \
	$(ROOT_DIR)/gui/client/commands/game/Seg.o \
	$(ROOT_DIR)/gui/client/commands/game/Smg.o \
	$(ROOT_DIR)/gui/client/commands/map/Msz.o \
	$(ROOT_DIR)/gui/client/commands/map/Mct.o \
	$(ROOT_DIR)/gui/client/commands/map/Bct.o \
	$(ROOT_DIR)/gui/client/commands/ressources/Pdr.o \
	$(ROOT_DIR)/gui/client/commands/ressources/Pgt.o \
	$(ROOT_DIR)/gui/client/commands/player/egg/Edi.o \
	$(ROOT_DIR)/gui/client/commands/player/egg/Pfk.o \
	$(ROOT_DIR)/gui/client/commands/player/egg/Ebo.o \
	$(ROOT_DIR)/gui/client/commands/player/egg/Enw.o \
	$(ROOT_DIR)/gui/client/commands/player/player/Pic.o \
	$(ROOT_DIR)/gui/client/commands/player/player/Pie.o \
	$(ROOT_DIR)/gui/client/commands/player/player/Pbc.o \
	$(ROOT_DIR)/gui/client/commands/player/player/Pnw.o \
	$(ROOT_DIR)/gui/client/commands/player/player/Plv.o \
	$(ROOT_DIR)/gui/client/commands/player/player/Pex.o \
	$(ROOT_DIR)/gui/client/commands/player/player/Ppo.o \
	$(ROOT_DIR)/gui/client/commands/player/player/Pdi.o \
	$(ROOT_DIR)/gui/client/commands/player/player/Pin.o

all: $(NAME)

$(NAME): $(OBJS_LINK)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS_LINK)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
