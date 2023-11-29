# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Directories
SRC_DIR = ./utils
OBJ_DIR = ./pipex_obj
LIBFT_DIR = ./libft

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard ./*.c)
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Program name
NAME = pipex

# Default rule
all: $(LIBFT) $(NAME)

# Rule to make the program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft

# Generic rule for objects
$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Libft compilation rule
$(LIBFT):
	make -C $(LIBFT_DIR)

# Clean rule
clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

# Full clean rule
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

# Rebuild rule
re: fclean all

.PHONY: all clean fclean re

