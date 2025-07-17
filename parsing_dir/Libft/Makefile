NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRC = ft_atoi.c ft_isdigit.c ft_strlcat.c ft_strnstr.c ft_itoa.c ft_putendl_fd.c\
ft_isalnum.c ft_isprint.c ft_strlcpy.c  ft_strrchr.c ft_split.c ft_strmapi.c ft_putnbr_fd.c\
ft_isalpha.c ft_strlen.c ft_tolower.c ft_strtrim.c ft_strjoin.c ft_striteri.c ft_putstr_fd.c\
ft_isascii.c ft_strchr.c ft_strncmp.c ft_toupper.c ft_memset.c ft_substr.c ft_putchar_fd.c\
ft_bzero.c ft_memcpy.c ft_memmove.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_strdup.c \

BONUS = ft_lstclear_bonus.c ft_lstadd_back_bonus.c\
ft_lstnew_bonus.c ft_lstdelone_bonus.c \
ft_lstmap_bonus.c ft_lstadd_front_bonus.c\
ft_lstlast_bonus.c ft_lstsize_bonus.c ft_lstiter_bonus.c\

OBJ = $(SRC:.c=.o)

OBONUS = $(BONUS:.c=.o)

all: $(NAME)

bonus: $(OBONUS)
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)
	ar rc $(NAME) $(OBJ)

$(OBONUS): $(BONUS)
	$(CC) $(CFLAGS) -c $(BONUS)
	ar rc $(NAME) $(OBONUS)

clean:
		$(RM) $(OBJ) $(OBONUS)

fclean: clean
		$(RM) $(NAME)

re: fclean all