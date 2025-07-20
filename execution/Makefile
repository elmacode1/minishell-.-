NAME = exec.a

SRC =	environ.c\
		execute.c\
		helpers.c\
		pipes.c\
		redirections.c\
		heredoc.c\
		builtins/export.c\
		builtins/pwd.c\
		builtins/cd.c\
		builtins/exit.c\
		builtins/unset.c\
		builtins/env.c\
		builtins/echo.c\
		builtins/builtins.c \
		signal.c\
		
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra 
LDFLAGS = -lreadline
CC	= cc

LIBFT = ../Libft/libft.a
LIBFT_DIR = ../Libft
INCLUDES = -I$(LIBFT_DIR)


all : $(NAME)


$(NAME) : $(OBJ)
	ar rcs  $@ $^

%.o : %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean : 
	rm -f $(OBJ)


fclean : clean
	rm -f $(NAME)

re : fclean all




