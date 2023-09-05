NAME = libft.a

SRCS_ = ft_isalpha\
		ft_isdigit\
		ft_isalnum\
		ft_isascii\
		ft_isprint\
		ft_strlen\
		ft_memset\
		ft_bzero\
		ft_memcpy\
		ft_memmove\
		ft_strlcpy\
		ft_strlcat\
		ft_toupper\
		ft_tolower\
		ft_strchr\
		ft_strrchr\
		ft_strncmp\
		ft_memchr\
		ft_memcmp\
		ft_strnstr\
		ft_atoi\
		ft_calloc\
		ft_strdup\
		ft_substr\
		ft_strjoin\
		ft_strtrim\
		ft_split\
		ft_itoa\
		ft_strmapi\
		ft_striteri\
		ft_putchar_fd\
		ft_putstr_fd\
		ft_putendl_fd\
		ft_putnbr_fd\
		ft_strnlen\
		ft_max\
		ft_min\
		ft_safe_free\
		ft_strcmp\
		ft_ltoa\
		ft_strtol\
		ft_isspace\
		ft_atoll\
		ft_strstr\
		ft_lstnew\
		ft_lstadd_front\
		ft_lstsize\
		ft_lstlast\
		ft_lstadd_back\
		ft_lstdelone\
		ft_lstclear\
		ft_lstiter\
		ft_lstmap
		
SRCS = $(addsuffix .c, $(SRCS_))
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror
CC = gcc

# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus