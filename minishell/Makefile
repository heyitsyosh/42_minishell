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
			expand/wildcard_expansion_utils\
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

OBJS_DIR = ./objs/
GNL_DIR = ./lib/gnl/
LIBFTPRINTF_DIR = ./lib/printf/

OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS = $(OBJS:.o=.d)

READLINE_LIB = -lreadline
GNL = ./lib/gnl/get_next_line.a
LIBFTPRINTF = ./lib/printf/libftprintf.a

ifeq ($(shell uname -s),Darwin)
	READLINE_LIB = -L$(shell brew --prefix readline)/lib
	READLINE_INCLUDE = -I$(shell brew --prefix readline)/include
else
	READLINE_LIB =
	READLINE_INCLUDE =
endif

CFLAGS = -Wall -Wextra -Werror
LIBS = -L$(LIBFTPRINTF_DIR) $(READLINE_LIB) -lftprintf -lreadline
#-fsanitize=address -g3
INCLUDES = -I ./includes $(READLINE_INCLUDE)

GREEN = \033[0;32m
NC = \033[0m

# Get brew and readline:
# 	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
#	brew update && brew upgrade && brew install readline

#--------------------------------------------------------------------------#

all: $(NAME)

$(OBJS_DIR)%.o: ./srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@printf "$(GREEN)Entering printf directory...$(NC)\n"
	@make --no-print-directory -C $(LIBFTPRINTF_DIR)
	@printf "$(GREEN)Entering get_next_line directory...$(NC)\n"
	@make --no-print-directory -C $(GNL_DIR)
	@printf "$(GREEN)Entering root directory...$(NC)\n"
	$(CC) $(INCLUDES) $(OBJS) -o $@ $(LIBS) $(LIBFTPRINTF) $(GNL)

clean:
	@make fclean --no-print-directory -C $(LIBFTPRINTF_DIR)
	@printf "$(GREEN)Entering get_next_line directory...$(NC)\n"
	@make fclean --no-print-directory -C $(GNL_DIR)
	@printf "$(GREEN)Entering root directory...$(NC)\n"
	rm -rf $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
