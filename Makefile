NAME = minishell

SRC_FILES = main\
			init_envp\
			signal/signal\
			tokenize/tokenize\
			tokenize/tokenize_utils\
			expand/expand\
			expand/word_to_list\
			expand/word_to_list_ii\
			expand/word_to_list_utils\
			expand/variable_expansion\
			expand/wildcard_expansion\
			parse/parse\
			parse/parse_cmd\
			parse/parse_redir\
			parse/parse_redir_utils\
			parse/parse_utils\
			execute/exec\
			execute/exec_builtin\
			execute/exec_nonbuiltin\
			execute/make_argv\
			execute/make_envp\
			pipeline/exec_pipeline\
			pipeline/pipeline_io\
			pipeline/pipeline_list\
			pipeline/wait\
			redirect/redirect\
			redirect/heredoc\
			utils/free\
			utils/error\
			utils/env_utils\
			utils/debug\
			utils/wrappers/x_close\
			utils/wrappers/x_dup\
			utils/wrappers/x_dup2\
			utils/wrappers/x_fork\
			utils/wrappers/x_strdup\
			utils/wrappers/x_strjoin_free\
			builtin/cd\
			builtin/cd_ii\
			builtin/echo\
			builtin/env\
			builtin/exit\
			builtin/export\
			builtin/pwd\
			builtin/unset

OBJ_DIR = ./objs

SRCS = $(foreach src,$(SRC_FILES),./srcs/$(src).c)
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:=.o))

FT_LIBFTPRINTF = ./lib/printf/libftprintf.a
GNL = ./lib/gnl/get_next_line.a 
LIBFTPRINTFDIR = ./lib/printf
GNLDIR = ./lib/gnl
READLINE_LIB = -lreadline 

ifeq ($(shell uname -s),Darwin)
	READLINE_LIB = -L$(shell brew --prefix readline)/lib
	READLINE_INCLUDE = -I$(shell brew --prefix readline)/include
else
	READLINE_LIB =
	READLINE_INCLUDE =
endif

CFLAGS = -Wall -Wextra -Werror
#-fsanitize=address -g3
LIBS = -L$(LIBFTPRINTFDIR) $(READLINE_LIB)  -lftprintf -lreadline
INCLUDES = -I ./includes $(READLINE_INCLUDE)

# Get brew and readline:
# 	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
#	brew update && brew upgrade && brew install readline

all: $(NAME)

$(OBJ_DIR)/%.o: ./srcs/%.c
	@mkdir -p $(dir $@) 
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

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

.PHONY: all clean fclean re