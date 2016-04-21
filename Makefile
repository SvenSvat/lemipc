##
## Makefile for malloc.c in /home/blanqu_a/rendu/PSU_2015_malloc
## 
## Made by Adrien Blanquer
## Login   <blanqu_a@epitech.net>
## 
## Started on  Sun Feb 14 22:59:48 2016 Adrien Blanquer
## Last update Thu Mar 24 16:12:33 2016 Adrien Blanquer
##

SRC	= AI.c \
	  aff_that.c \
	  check_alive.c \
	  creat_champion.c \
	  main.c \
	  move_champ.c \
	  init.c

OBJ	= $(SRC:.c=.o)

NAME	= lemipc

CC	= gcc

CFLAGS	+= -Wall -Wextra -Werror -W -g3

LDFLAGS	= -lm

all:	$(NAME)

$(NAME): $(OBJ)
	 $(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
