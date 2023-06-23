NAME = minishell

SRC_FILES = main \
			init_envp \
			run_line \
			tokenize/tokenize\
			tokenize/tokenize_utils \
			expand/expand \
			expand/word_to_list \
			expand/word_to_list_ii \
			expand/word_to_list_utils \
			expand/variable_expansion \
			expand/wildcard_expansion \
			parse/parse \
			parse/parse_cmd \
			parse/parse_redir \
			parse/parse_redir_utils \
			parse/parse_utils \
			utils/free \
			utils/error \
			utils/env_utils \
			utils/xstrdup \
			utils/debug \
			execute/exec \
			execute/exec_cmd \
			execute/exec_execve \
			execute/make_argv \
			builtin/cd\
			builtin/echo\
			builtin/env\
			builtin/exit\
			builtin/export\
			builtin/export_ii\
			builtin/pwd\
			builtin/unset\

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