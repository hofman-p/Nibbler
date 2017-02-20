##
## Makefile for openGL in /home/royer_q/depots/cpp_nibbler/openGL
##
## Made by Quentin ROYER
## Login   <royer_q@epitech.net>
##
## Started on  Fri Mar 14 14:10:58 2014 Quentin ROYER
## Last update Sat Apr  5 15:01:45 2014 Quentin ROYER
##

CC			= g++

SRCS			= OpenGLGI.cpp \
			PNGLoader.cpp

OBJS			= $(SRCS:.cpp=.o)

NAME			= lib_nibbler_openGL.so

CPPFLAGS		= -W -Wall -Werror -Wextra

LIBS			= -lglut -lGLU -lGL -lpng -lglfw

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
