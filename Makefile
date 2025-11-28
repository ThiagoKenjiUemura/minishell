# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 13:27:50 by thiagouemur       #+#    #+#              #
#    Updated: 2025/11/28 17:53:51 by liferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc

BREW_RL := $(shell brew --prefix readline 2>/dev/null)

CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/ -g3 \
		 $(if $(BREW_RL),-I$(BREW_RL)/include,)

LIBFT_DIR= libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LDFLAGS = -L$(LIBFT_DIR) $(if $(BREW_RL),-L$(BREW_RL)/lib,)
LDLIBS = -lft -lreadline

SRCS = src/main.c \
	src/parsing/input_parser.c \
	src/parsing/count_token.c \
	src/parsing/lexer.c \
	src/parsing/lexer_utils.c \
	src/parsing/token_utils.c \
	src/parsing/parser.c \
	src/parsing/parser_utils.c \
	src/parsing/parser_utils2.c \
	src/parsing/expander_utils.c \
	src/parsing/expander_utils2.c \
	src/parsing/expander.c \
	src/parsing/quote_removal.c \
	src/parsing/heredoc.c \
	src/parsing/heredoc_utils.c \
	src/signals/signals.c \
	src/envp/env_init.c \
	src/builtins/builtin.c \
	src/builtins/builtin_pwd.c \
	src/builtins/builtin_cd.c \
	src/builtins/builtin_env.c \
	src/builtins/builtin_echo.c \
	src/builtins/builtin_exit.c \
	src/builtins/builtin_export.c \
	src/builtins/builtin_unset.c \
	src/builtins/builtin_utils.c \
	src/garbage/garbage_utils.c \
	src/garbage/garbage.c \
	src/execute/execute.c \
	src/execute/execute_external.c \
	src/execute/path.c \
	src/execute/execute_utils.c \
	src/execute/redirection/redirection.c \
	src/execute/redirection/redirection_utils.c \
	src/execute/redirection/redirection_check.c \
	src/execute/redirection/redirection_builtin_exec.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LDLIBS)
	@echo "Minishell ready!"

$(LIBFT_A):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) all

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning libft..."
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Cleaning objects..."
	@rm -f $(OBJS)

fclean: clean
	@echo "Cleaning libft.a..."
	@$(MAKE) -C libft fclean
	@echo "Cleaning $(NAME)..."
	@rm -f $(NAME)

re: fclean all

val: readline.supp all
	@valgrind -q --suppressions=readline.supp \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				--trace-children=yes \
				--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
				./${NAME}

.PHONY: all clean fclean re