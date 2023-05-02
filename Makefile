##
## EPITECH PROJECT, 2023
## Arcade
## File description:
## Makefile
##

CORE_SRC	=	src/utils/FileUtils.cpp	\
				src/utils/ScoreSaver.cpp	\
				src/core/Core.cpp	\
				src/main.cpp

CORE_OBJ	=	$(CORE_SRC:.cpp=.o)

LIB_PATH	=	./lib/

## GAMES ##
SNAKE_SRC	=	src/games/Snake/Snake.cpp

SNAKE_OBJ	=	$(SNAKE_SRC:.cpp=.o)

SNAKE_LIBNAME	=	arcade_snake.so


PACMAN_SRC	=	src/games/Pacman/Pacman.cpp	\
				src/games/Pacman/Ghost.cpp

PACMAN_OBJ	=	$(PACMAN_SRC:.cpp=.o)

PACMAN_LIBNAME	=	arcade_pacman.so


NIBBLER_SRC	=	src/games/Nibbler/Nibbler.cpp

NIBBLER_OBJ	=	$(NIBBLER_SRC:.cpp=.o)

NIBBLER_LIBNAME	=	arcade_nibbler.so

## GRAPHIC LIBRARIES ##
NCURSES_SRC	=	src/graphicLibs/Ncurses/Ncurses.cpp

NCURSES_OBJ	=	$(NCURSES_SRC:.cpp=.o)

NCURSES_LIBNAME	=	arcade_ncurses.so

NCURSES_FLAGS	=	-lcurses

SDL2_SRC	=	src/graphicLibs/Sdl2/Sdl2.cpp

SDL2_OBJ	=	$(SDL2_SRC:.cpp=.o)

SDL2_LIBNAME	=	arcade_sdl2.so

SDL2_FLAGS	=	-lSDL2 -lSDL2_ttf -lSDL2_image

SFML_SRC	=	src/graphicLibs/Sfml/Sfml.cpp

SFML_OBJ	=	$(SFML_SRC:.cpp=.o)

SFML_LIBNAME	=	arcade_sfml.so

SFML_FLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CXXFLAGS	=	-std=c++20 -Wall -Wextra -g3 -pedantic -fPIC -fno-gnu-unique

CPPFLAGS	=	-I./include/ -I./src/errors/ -I./src/core/ -I./src/utils/ -I./src/

SHARED_FLAGS	=	-shared $(CPPFLAGS)

LIBDL	=	-ldl

CC	=	g++

CORE_NAME	=	arcade

all:	core games graphicals

games:	$(SNAKE_LIBNAME) $(PACMAN_LIBNAME) $(NIBBLER_LIBNAME)

$(SNAKE_LIBNAME):	$(SNAKE_OBJ)
	$(CC) -o $(LIB_PATH)$(SNAKE_LIBNAME) $(SNAKE_OBJ) $(SHARED_FLAGS)

$(PACMAN_LIBNAME):	$(PACMAN_OBJ)
	$(CC) -o $(LIB_PATH)$(PACMAN_LIBNAME) $(PACMAN_OBJ) $(SHARED_FLAGS)

$(NIBBLER_LIBNAME):	$(NIBBLER_OBJ)
	$(CC) -o $(LIB_PATH)$(NIBBLER_LIBNAME) $(NIBBLER_OBJ) $(SHARED_FLAGS)

graphicals:	$(NCURSES_LIBNAME) $(SFML_LIBNAME) $(SDL2_LIBNAME)

$(SFML_LIBNAME): $(SFML_OBJ)
	$(CC) -o $(LIB_PATH)$(SFML_LIBNAME) $(SFML_OBJ) $(SHARED_FLAGS) $(SFML_FLAGS)

$(NCURSES_LIBNAME):	$(NCURSES_OBJ)
	$(CC) -o $(LIB_PATH)$(NCURSES_LIBNAME) $(NCURSES_OBJ) $(SHARED_FLAGS) $(NCURSES_FLAGS)

$(SDL2_LIBNAME): $(SDL2_OBJ)
	$(CC) -o $(LIB_PATH)$(SDL2_LIBNAME) $(SDL2_OBJ) $(SHARED_FLAGS) $(SDL2_FLAGS)

core:	$(CORE_OBJ)
	$(CC) -o $(CORE_NAME) $(CORE_OBJ) $(FNOFLAGS) $(LIBDL) $(CPPFLAGS)
	
clean:
	$(RM) $(CORE_OBJ)
	$(RM) $(SNAKE_OBJ)
	$(RM) $(PACMAN_OBJ)
	$(RM) $(NIBBLER_OBJ)
	$(RM) $(NCURSES_OBJ)
	$(RM) $(SFML_OBJ)
	$(RM) $(SDL2_OBJ)

fclean: clean
	$(RM) $(CORE_NAME)
# $(RM) $(LIB_PATH)$(SNAKE_LIBNAME)
# $(RM) $(LIB_PATH)$(NCURSES_LIBNAME)
# $(RM) $(LIB_PATH)$(NIBBLER_LIBNAME)
# $(RM) $(LIB_PATH)$(PACMAN_LIBNAME)
# $(RM) $(LIB_PATH)$(SFML_LIBNAME)
# $(RM) $(LIB_PATH)$(SDL2_LIBNAME)

#%.o	:	%.cpp
#	$(CC) -c $(CPPFLAGS) $(IFLAGS) $< -o $@

re: fclean all

.PHONY : all re clean fclean
