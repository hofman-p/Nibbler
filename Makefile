##
## Makefile for nibbler in /home/royer_q/nibbler
## 
## Made by Quentin ROYER
## Login   <royer_q@epitech.net>
## 
## Started on  Tue Mar 11 21:44:43 2014 Quentin ROYER
## Last update Sun Apr  6 21:13:42 2014 Quentin ROYER
##

CC			= g++ -g

SRCS			= main.cpp \
			DLLoader.cpp \
			Launcher.cpp \
			Clock.cpp \
			Nibbler.cpp \
			Map.cpp \
			Snake.cpp \
			DynamicElement.cpp \
			Element.cpp

OBJS			= $(SRCS:.cpp=.o)

NAME			= nibbler

CPPFLAGS		= -W -Wall -Werror -Wextra

LIBS			= -ldl -lboost_thread

$(NAME):		$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(LIBS) $(CPPFLAGS)
			@make --no-print-directory -C SFML/
			@make --no-print-directory -C SDL/
			@make --no-print-directory -C openGL/
			@make --no-print-directory -C Xlib/
			@make --no-print-directory -C Bonus/openGL3D/

all:			$(NAME)

clean:
			rm -rf $(OBJS)
			@make clean --no-print-directory -C SFML/
			@make clean --no-print-directory -C SDL/
			@make clean --no-print-directory -C openGL/
			@make clean --no-print-directory -C Xlib/
			@make clean --no-print-directory -C Bonus/openGL3D/

fclean:			clean
			rm -rf $(NAME)
			@make fclean --no-print-directory -C SFML/
			@make fclean --no-print-directory -C SDL/
			@make fclean --no-print-directory -C openGL/
			@make fclean --no-print-directory -C Xlib/
			@make fclean --no-print-directory -C Bonus/openGL3D/

re:			fclean all
