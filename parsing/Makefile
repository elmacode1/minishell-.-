NAME = parsing.a

SRC = 	lexer.c utils.c token_utils.c syntax_error.c parser.c g_collector.c expander.c
		
OBJ = $(SRC:.c=.o)

FLAGS = -Wall  -Wextra 
LDFLAGS = -lreadline
CC	= gcc

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs  $@ $^

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all