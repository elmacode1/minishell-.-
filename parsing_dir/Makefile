NAME = minishell

SRC = 	lexer.c utils.c token_utils.c syntax_error.c parser.c
		
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra 
LDFLAGS = -lreadline
CC	= gcc

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C libft_malak

	$(CC) $(FLAGS) $(OBJ) libft_malak/libft.a -o  $(NAME) $(LDFLAGS)

clean : 
	rm -f $(OBJ)
	@make -C libft_malak clean

fclean : clean
	rm -f $(NAME)
	@make -C libft_malak fclean

re : fclean all