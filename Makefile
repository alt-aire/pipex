CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
NAME    = pipex
LIBNAME = libpipex.a
AR      = ar rcs
INCLUDES= -Iincludes
SRC     = src/pipex/pipex_utils.c \
          src/pipex/split_utils.c \
          src/pipex/split.c \
          src/pipex/path.c \
		  src/libft/libft.c	  
MAIN    = src/main.c
OBJ = $(SRC:.c=.o)
MAINOBJ  = $(MAIN:.c=.o)

all: $(LIBNAME) $(NAME)

$(LIBNAME): $(OBJ)
	$(AR) $(LIBNAME) $(OBJ)

$(NAME): $(LIBNAME) $(MAINOBJ)
	$(CC) $(CFLAGS) $(MAINOBJ) $(INCLUDES) -L. -lpipex -o $(NAME)

src/%.o: src/%.c includes/pipex.h includes/libft.h Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(MAINOBJ)

fclean: clean
	rm -f $(NAME) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re