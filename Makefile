NAME = minishell

SRC =	main_helpers.c main.c\
		
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra #-g -fsanitize=address
LDFLAGS = -lreadline
CC	= cc 

# READLINE_INC = -I$(shell brew --prefix readline)/include
# READLINE_LIB = -L$(shell brew --prefix readline)/lib
# LDFLAGS = $(READLINE_LIB) -lreadline

EXEC = execution/exec.a
EXEC_DIR = execution

PARS = parsing/parsing.a
PARS_DIR = parsing

LIBFT = Libft/libft.a
LIBFT_DIR = Libft

INCLUDES = -I$(LIBFT_DIR) -I$(EXEC_DIR) -I$(PARS_DIR)
# INCLUDES = -I$(LIBFT_DIR) -I$(EXEC_DIR) -I$(PARS_DIR) $(READLINE_INC)


all : $(NAME) 

$(NAME) : $(OBJ) $(PARS) $(EXEC) $(LIBFT)
	$(CC) $(FLAGS) $^ -o  $@ $(LDFLAGS)

$(EXEC) :	FORCE
	make -C $(EXEC_DIR)
# 		READLINE_INC="$(READLINE_INC)" \
# 		READLINE_LIB="$(READLINE_LIB)"
# 		should remove this later just for mac

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

