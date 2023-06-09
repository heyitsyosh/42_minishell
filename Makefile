NAME = minishell

SRC_FILES = main\
			init_envp\
			env_utils\
			tokenize\
			tokenize_utils\
			parse\
			expand\
			exec\
			free\
			redirect\
			error\
			builtin\cd\
			builtin\echo\
			builtin\env\
			builtin\exit\
			builtin\export\
			builtin\pwd\
			builtin\unset\

SRCS = $(foreach src,$(SRC_FILES),./srcs/$(src).c)
OBJS = $(SRCS:.c=.o)

INCLUDES = -I ./includes

LIBFTPRINTFDIR = ./lib/printf
GNLDIR = ./lib/gnl

FT_LIBFTPRINTF = ./lib/printf/libftprintf.a
GNL = ./lib/gnl/get_next_line.a 

LIBS = -lreadline -L$(LIBFTPRINTFDIR) -lftprintf

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTPRINTFDIR)
	make -C $(GNLDIR)
	gcc $(INCLUDES) $(OBJS) -o $@ $(LIBS) $(FT_LIBFTPRINTF) $(GNL)

clean:
	make fclean -C $(LIBFTPRINTFDIR)
	make fclean -C $(GNLDIR)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re