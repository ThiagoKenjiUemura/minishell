# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 13:27:50 by thiagouemur       #+#    #+#              #
#    Updated: 2025/11/17 16:38:09 by liferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/

LIBFT_DIR= libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LDFLAGS = -L$(LIBFT_DIR)
LDLIBS = -lft -lreadline

SRCS = src/main.c \
	src/parsing/input_parser.c \
	src/parsing/count_token.c \
	src/parsing/lexer.c \
	src/parsing/token_utils.c \
	src/signals/signals.c \
	src/envp/env_init.c \
	src/builtins/builtin.c \
	src/builtins/builtin_exit.c \
	src/builtins/builtin_cd.c \
	src/builtins/builtin_env.c \
	src/builtins/builtin_echo.c \
	src/garbage.c \

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

.PHONY: all clean fclean re