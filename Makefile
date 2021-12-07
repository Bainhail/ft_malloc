#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabihali <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 04:19:55 by nabihali          #+#    #+#              #
#    Updated: 2021/12/07 15:52:15 by nabihali         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	libft_malloc_

HOST		=	$(shell hostname)

CC	 		=	gcc

CFLAG		+=	-g -Wall -Wextra -Werror

FLAG_SRC	=	-c -fPIC

FLAG_LIB	=	-shared -o

SRC			=	initialise.c \
				ft_malloc.c	\
				ft_free.c	\
				ft_realloc.c \
				ft_print_str.c \
				print_mem.c \
				heap_func.c \
				spot_locator.c \
				block_func.c

SRC_EXEC	=	main.c

OBJ			=	$(SRC:.c=.o)

OBJ_EXEC	=	$(SRC_EXEC:.c=.o)

.PHONY:		all

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) $(CFLAG) $(FLAG_LIB) $(NAME)$(HOST).so

%.o:		%.c
			$(CC) $(FLAG_SRC) $(CFLAG) $^ -o $@

clean:
			rm -f $(OBJ) $(OBJ_EXEC)

fclean:		clean
			rm -f $(NAME)$(HOST).so
			rm -f exec_test

re:			fclean all
