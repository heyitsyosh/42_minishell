NAME = minishell

SRC_FILES = main \
			init_envp \
			signal/signal \
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
			utils/x_strdup \
			utils/debug \
			execute/exec \
			execute/exec_builtin \
			execute/exec_nonbuiltin \
			execute/make_argv \
			execute/make_envp \
			redirect/redirect \
			redirect/heredoc \
			builtin/cd\
			builtin/echo\
			builtin/env\
			builtin/exit\
			builtin/export\
			builtin/export_ii\
			builtin/pwd\
			builtin/unset\

OBJ_DIR = ./objs

SRCS = $(foreach src,$(SRC_FILES),./srcs/$(src).c)
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:=.o))

INCLUDES = -I ./includes 
# -fsanitize=address -g3

LIBFTPRINTFDIR = ./lib/printf
GNLDIR = ./lib/gnl

FT_LIBFTPRINTF = ./lib/printf/libftprintf.a
GNL = ./lib/gnl/get_next_line.a 

LIBS = -lreadline -L$(LIBFTPRINTFDIR) -lftprintf

all: $(NAME)

$(OBJ_DIR)/%.o: ./srcs/%.c
	@mkdir -p $(dir $@) 
	gcc $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFTPRINTFDIR)
	make -C $(GNLDIR)
	gcc $(INCLUDES) $(OBJS) -o $@ $(LIBS) $(FT_LIBFTPRINTF) $(GNL)

clean:
	make fclean -C $(LIBFTPRINTFDIR)
	make fclean -C $(GNLDIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

readline: 
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew update && brew upgrade && brew install readline

.PHONY: all clean fclean re