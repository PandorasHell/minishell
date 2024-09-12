# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror -g3 -fsanitize=address#,leak


# Directories
SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
LIBFT_DIR := $(LIB_DIR)/libft

# Source files
SRC_FILES := 	$(SRC_DIR)/main.c \
				$(SRC_DIR)/env/env.c \
				$(SRC_DIR)/parsing/malloc_check.c \
				$(SRC_DIR)/lexer/lexer.c \
				$(SRC_DIR)/lexer/lexer_utils.c \
				$(SRC_DIR)/lexer/split_words.c \
				$(SRC_DIR)/lexer/word_lexer_free.c \
				$(SRC_DIR)/parser/parser.c \
				$(SRC_DIR)/parser/set_values.c \
				$(SRC_DIR)/parser/status_checker.c \
				$(SRC_DIR)/utils/exit_checker.c \

# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Libraries
LIBS := -L$(LIBFT_DIR) -lft -lreadline

# Executable
TARGET := minishell
NAME := $(TARGET)

# Conditional compilation based on target
ifeq ($(MAKECMDGOALS),debug)
 CFLAGS += -g
else ifeq ($(MAKECMDGOALS),optimize)
 CFLAGS += -O2
endif

all: libft $(TARGET)

# Libft targets
libft:
	$(MAKE) -C $(LIBFT_DIR)

libft_clean:
	$(MAKE) -C $(LIBFT_DIR) clean

libft_fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean

clean: libft_clean 
	rm -rf $(OBJ_DIR)

fclean: clean libft_fclean 
	rm -f $(TARGET)

re: fclean all

bonus:: CFLAGS += -D BONUS=1
bonus: re

rebonus: fclean bonus

# Build rule
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Object file rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
.PHONY: all clean fclean re bonus rebonus

