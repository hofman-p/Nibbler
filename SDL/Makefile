##
## Makefile for nibbler in /home/royer_q/depots/cpp_nibbler/SDL
## 
## Made by Quentin ROYER
## Login   <royer_q@epitech.net>
## 
## Started on  Sun Apr  6 14:52:58 2014 Quentin ROYER
## Last update Sun Apr  6 14:56:52 2014 Quentin ROYER
##

NAME		= lib_nibbler_SDL.so

SRCS		= SDLGI.cpp

OBJS		= $(SRCS:.cpp=.o)

CC		= g++

LIBS		= -lSDL -lSDL_image -lSDL_ttf

CPPFLAGS	= -W -Wall -Wextra -Werror

$(NAME):
		$(CC) -fPIC -c $(SRCS)
		$(CC) -shared -o $(NAME) $(OBJS) $(LIBS) $(CPPFLAGS)
		mv $(NAME) ../lib/

all:		$(NAME)

clean:
		rm -rf $(OBJS)

fclean:		clean
		rm -rf ../lib/$(NAME)

re:		fclean	all
