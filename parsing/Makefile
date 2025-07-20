NAME = parsing

SRC = 	lexer.c utils.c token_utils.c syntax_error.c parser.c g_collector.c expander.c
		
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra 
LDFLAGS = -lreadline
CC	= gcc

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o  $(NAME) $(LDFLAGS)

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all