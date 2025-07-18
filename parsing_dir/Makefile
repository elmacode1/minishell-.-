NAME = minishell

SRC = 	lexer.c utils.c token_utils.c syntax_error.c parser.c g_collector.c
		
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra 
LDFLAGS = -lreadline
CC	= gcc

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C Libft

	$(CC) $(FLAGS) $(OBJ) Libft/libft.a -o  $(NAME) $(LDFLAGS)

clean : 
	rm -f $(OBJ)
	@make -C Libft clean

fclean : clean
	rm -f $(NAME)
	@make -C Libft fclean

re : fclean all