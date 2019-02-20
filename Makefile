##
## EPITECH PROJECT, 2019
## malloc
## File description:
## Makefile
##

CC		=	gcc

CFLAGS	=	-W -Wall -Wextra  -g3

SRC_NM		=	nm/main.c	\

SRC_OBJDUMP		=	objdump/main.c	\
					objdump/create.c	\
					objdump/destroy.c	\
					objdump/flags.c		\
					objdump/tool.c		\
					objdump/tool32.c		\
					objdump/other.c		\
					objdump/dump_sys_32.c	\
					objdump/dump_sys_64.c	\

OBJ_NM		=	$(SRC_NM:.c=.o)
OBJ_OBJDUMP		=	$(SRC_OBJDUMP:.c=.o)

NAME_NM	=	my_nm
NAME_OBJDUMP	=	my_objdump

all:		nm objdump

nm:	$(OBJ_NM)
		$(CC) -o $(NAME_NM) $(OBJ_NM)

objdump:	$(OBJ_OBJDUMP)
		$(CC) -o $(NAME_OBJDUMP) $(OBJ_OBJDUMP)

clean:
		rm -f $(OBJ_NM)
		rm -f $(OBJ_OBJDUMP)

fclean:		clean
		rm -f $(NAME_NM)
		rm -f $(NAME_OBJDUMP)

re:		fclean all
