# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/14 11:46:06 by liferrei          #+#    #+#              #
#    Updated: 2025/10/28 17:53:45 by tkenji-u         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SRC = \
    ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
    ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
    ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
    ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
    ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
    ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
    ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
    ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c\
    ft_putnbr_fd.c ft_putendl_fd.c get_next_line.c \
    ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
    ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
    ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ = $(SRC:.c=.o)

FT_PRINTF_DIR = ft_printf
FT_PRINTF_A = $(FT_PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ) $(FT_PRINTF_A)
	@cp $(FT_PRINTF_DIR)/*.o .
	@$(AR) $(NAME) $(OBJ) *.o
	@rm -f *.o

$(FT_PRINTF_A):
	@$(MAKE) -C $(FT_PRINTF_DIR) all

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus:

clean:
	@$(MAKE) clean -C $(FT_PRINTF_DIR)
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(FT_PRINTF_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus