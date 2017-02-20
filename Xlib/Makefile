##
## Makefile for SFML in /home/royer_q/nibbler/SFML
## 
## Made by Quentin ROYER
## Login   <royer_q@epitech.net>
## 
## Started on  Tue Mar 11 21:49:32 2014 Quentin ROYER
## Last update Thu Apr  3 01:27:49 2014 Quentin ROYER
##

CC			= g++

SRCS			= XlibGI.cpp

OBJS			= $(SRCS:.cpp=.o)

NAME			= lib_nibbler_Xlib.so

CPPFLAGS		= -W -Wall -Werror -Wextra

LIBS			= -lX11

$(NAME):
			$(CC) -fPIC -c $(SRCS)
			$(CC) -shared -o $(NAME) $(OBJS) $(LIBS) $(CPPFLAGS)
			mv $(NAME) ../lib

all:			$(NAME)

clean:
			rm -rf $(OBJS)

fclean:			clean
			rm -rf ../lib/$(NAME)

re:			fclean all
