NAME = minishell

LEXER = create_env_list.c env_list_to_array.c

SRC = $(addprefix src/lexer/env_functions/,$(LEXER))\
		src/main.c

BREW_DIR		= $(shell brew --prefix)
LIBREADLINE		= $(BREW_DIR)/opt/readline/lib

FLAGS = -Wall -Werror -Wextra

INCLUDE_DIRS = -Isrc/libft -Iinclude -I$(BREW_DIR)/opt/readline/include 

# LIB_DIRS = -Lsrc/libft -llibft  -L$(LIBREADLINE) -lreadline 
LIB_DIRS = src/libft/libft.a $(LIBREALINE)/readline

OBJ_DIR = obj

OBJ = $(SRC:%.c=%.o)

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ) 
	make -C src/libft
	gcc $(OBJ) $(FLAGS) $(LIB_DIRS) -o minishell

$(OBJ_DIR)/%.o: %.c
	gcc -c $^ -o $@ $(FLAGS) $(INCLUDE_DIRS)

$(OBJ_DIR):
	mkdir obj

clean:
	make clean -C src/libft
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C src/libft
	rm -f minishell

re: fclean all

# testing: testing.c
# 	gcc testing.c -L$(LIBREADLINE) -l readline -I $(BREW_DIR)/opt/readline/include -fsanitize=address -g -o testing

# testing2: testing2.c
# 	gcc ft_split.c ft_split_putstr.c testing2.c -L$(LIBREADLINE) -l readline -I $(BREW_DIR)/opt/readline/include -o testing2
