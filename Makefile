NAME = minishell

SRC =	main.c\
		
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra 
LDFLAGS = -lreadline
CC	= cc

EXEC = execution/exec.a
EXEC_DIR = execution

LIBFT = Libft/libft.a
LIBFT_DIR = Libft

INCLUDES = -I$(LIBFT_DIR) -I$(EXEC_DIR)

all : $(NAME)

$(NAME) : $(OBJ) $(EXEC) $(LIBFT)
	$(CC) $(FLAGS) $^ -o  $@ $(LDFLAGS)

$(EXEC) :
	make -C $(EXEC_DIR)

$(LIBFT) :
	make -C $(LIBFT_DIR)



%.o : %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean : 
	rm -f $(OBJ)
	make clean -C $(EXEC_DIR)
	make clean -C $(LIBFT_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(EXEC_DIR)
	make fclean -C $(LIBFT_DIR)

re : fclean all




