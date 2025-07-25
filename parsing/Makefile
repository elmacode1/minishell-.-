NAME = parsing.a

SRC = 	lexer.c utils.c token_utils.c syntax_error.c parser.c g_collector.c expander.c
		
OBJ = $(SRC:.c=.o)

FLAGS = -Wall  -Wextra 
LDFLAGS = -lreadline
CC	= gcc

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