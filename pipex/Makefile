NAME	=	pipex
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror #-g3 -fsanitize=address
LFT		=	libft/libft.a
OBJ		=	$(SRCS:.c=.o)
SRCS	=	pipex.c \
			child.c \
			exec.c	\
			utils.c


all:		$(LFT) $(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) -o $@ $^ $(LFT)
			@echo "\033[32m[✔] $(NAME) compiled!\033[0m"

$(LFT):	
			@make -s -C libft
			@echo "\033[32m[✔] $(LFT) compiled!\033[0m"

$(OBJ):	%.o: %.c
			@$(CC) $(CFLAGS) -c -o $@ $<

clean:
			@make -s $@ -C libft
			@rm -rf $(OBJ) $(LFT)
			@echo "\033[31m[✘] $(NAME) objects deleted!\033[0m"

fclean:		clean
			@rm -rf $(NAME)
			@echo "\033[31m[✘] $(NAME) deleted!\033[0m"

re:			fclean all

.PHONY:		all clean fclean re
		