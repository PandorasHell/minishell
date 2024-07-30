# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 16:43:22 by smeixoei          #+#    #+#              #
#    Updated: 2023/08/09 10:17:12 by smeixoei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
FLAGS = -Wall -Werror -Wextra
LIB = ar -rcs
INCLUDES = libft.h
SRCS_MAIN = ft_isdigit.c\
			ft_isalnum.c\
			ft_isascii.c\
			ft_isprint.c\
			ft_strlen.c\
			ft_strlcpy.c\
			ft_strlcat.c\
			ft_atoi.c\
			ft_memset.c\
			ft_memcpy.c\
			ft_toupper.c\
			ft_tolower.c\
			ft_isalpha.c\
			ft_bzero.c\
			ft_strncmp.c\
			ft_memmove.c\
			ft_strchr.c\
			ft_strrchr.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_strnstr.c\
			ft_calloc.c\
			ft_strdup.c\
			ft_strjoin.c\
			ft_itoa.c\
			ft_substr.c\
			ft_strmapi.c\
			ft_striteri.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_strtrim.c\
			ft_split.c\
			get_next_line.c\
			get_next_line_utils.c\

OBJS_MAIN = $(SRCS_MAIN:.c=.o)

RM = rm -f

all: $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) $?

$(NAME): $(OBJS_MAIN) $(INCLUDES)
		$(LIB) $(NAME) $(OBJS_MAIN)

clean:
	$(RM) $(OBJS_MAIN) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean res
