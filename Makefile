NAME = minishell

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
		main.c\
		
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra 
LDFLAGS = -lreadline
CC	= cc
LIBFT = Libft/libft.a
LIBFT_DIR = Libft
INCLUDES = -I$(LIBFT_DIR)

all : $(LIBFT) $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o  $(NAME) $(LDFLAGS)

%.o : %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean : 
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re : fclean all




