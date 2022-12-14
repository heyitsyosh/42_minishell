NAME = minishell
# BONUS_NAME = 

LIBFTDIR = ./lib/libft
PRINTFDIR = ./lib/printf
GNLDIR = ./lib/gnl
DIR = ./mandatory_myoshika
# BONUS_DIR = ./bonus

FT_PRINTF = ./lib/printf/libftprintf.a -L$(PRINTFDIR) -lftprintf
GNL = ./lib/gnl/get_next_line.a
READLINE = -lreadline

FILES = main\
		init_envp\
		env_utils\
		tokenize\
		tokenize_general\
		tokenize_operator\
		tokenize_quoted\
		utils\
		builtin/env
# BONUS_FILES = 

SRCS = $(foreach src,$(FILES),./mandatory_myoshika/$(src).c)
OBJS = $(SRCS:.c=.o)
BONUS_SRCS = $(foreach bonus_src,$(BONUS_FILES),./bonus/$(bonus_src)_bonus.c)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I ./includes
CC = gcc

#--------------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(PRINTFDIR)
	make -C $(GNLDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(FT_PRINTF) $(GNL) $(READLINE)

# bonus: $(BONUS_NAME)

# $(BONUS_NAME): $(BONUS_OBJS)
# 	make -C $(PRINTFDIR)
# 	make -C $(GNLDIR)
# 	$(CC) $(CFLAGS) -o $@ $(BONUS_OBJS) $(FT_PRINTF) $(GNL)

clean:
	make fclean -C $(PRINTFDIR)
	make fclean -C $(GNLDIR)
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus