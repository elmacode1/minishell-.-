NAME = minishell

SRC =	main_helpers.c main.c\
		
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra #-g -fsanitize=address
LDFLAGS = -lreadline
CC	= cc

EXEC = execution/exec.a
EXEC_DIR = execution

PARS = parsing/parsing.a
PARS_DIR = parsing

LIBFT = Libft/libft.a
LIBFT_DIR = Libft

INCLUDES = -I$(LIBFT_DIR) -I$(EXEC_DIR) -I$(PARS_DIR)

all : $(NAME) 

$(NAME) : $(OBJ) $(PARS) $(EXEC) $(LIBFT)
	$(CC) $(FLAGS) $^ -o  $@ $(LDFLAGS)

$(EXEC) :	FORCE
	make -C $(EXEC_DIR)

$(LIBFT) :	FORCE
	make -C $(LIBFT_DIR)

$(PARS) :	FORCE
	make -C $(PARS_DIR)

FORCE:

%.o : %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean : 
	rm -f $(OBJ)
	make clean -C $(EXEC_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(PARS_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(EXEC_DIR)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PARS_DIR)


re : fclean all


.PHONY: all clean fclean FORCE re 

