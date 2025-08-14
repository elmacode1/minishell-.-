NAME = exec.a

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
		builtins/export_utils.c\
		signal.c\
		execute_extern_utils.c\
		execute_extern.c\
		execute_builtin.c\
		pipes_utils.c\
		helpers2.c
		
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra 
# LDFLAGS = $(READLINE_LIB) -lreadline
LDFLAGS = -lreadline
CC	= cc	

LIBFT = ../Libft/libft.a
LIBFT_DIR = ../Libft
INCLUDES = -I$(LIBFT_DIR) $(READLINE_INC)


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
