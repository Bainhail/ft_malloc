ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		=	libft_malloc_$(HOSTTYPE).so
SHRT_NAME   =	libft_malloc.so

CC	 		=	gcc

CFLAG		+=	-Wall -Wextra -Werror

FLAG_SRC	=	-c -fPIC

FLAG_LIB	=	-shared -o

SRC			=	initialise.c	\
				ft_malloc.c		\
				ft_free.c		\
				ft_realloc.c	\
				ft_print_str.c	\
				print_mem.c		\
				heap_func.c		\
				spot_locator.c	\
				block_func.c

SRC_EXEC	=	main.c

OBJ			=	$(SRC:.c=.o)

OBJ_EXEC	=	$(SRC_EXEC:.c=.o)

.PHONY:		all

all:		$(NAME) $(SHRT_NAME)

$(SHRT_NAME):
		ln -s $(NAME) $(SHRT_NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(CFLAG) $(FLAG_LIB) $(NAME)

%.o:		%.c
		$(CC) $(FLAG_SRC) $(CFLAG) $^ -o $@

clean:
		rm -f $(OBJ) $(OBJ_EXEC)

fclean:		clean
		rm -f $(NAME)
		rm -f $(SHRT_NAME)
		rm -f exec_test

re:		fclean all