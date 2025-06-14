NAME = minishell

SRC = 	lexer.c utils.c token_utils.c syntax_error.c parsin.c
		
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra 
LDFLAGS = -lreadline
CC	= gcc

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C libft

	$(CC) $(FLAGS) $(OBJ) libft/libft.a -o  $(NAME) $(LDFLAGS)

clean : 
	rm -f $(OBJ)
	@make -C libft clean

fclean : clean
	rm -f $(NAME)
	@make -C libft fclean

re : fclean all