NAME = minishell

LEXER =		lexer.c										\
			in_string.c									\
			check_syntax_error.c						\

ENV_FUNC =	create_env_vars_list.c						\
			add_env_node.c								\
			env_list_to_array.c							\
			
SRC =	$(addprefix src/env_functions/,$(ENV_FUNC))		\
		$(addprefix src/lexer/, $(LEXER))				\
		src/main.c

BREW_DIR		= $(shell brew --prefix)
LIBREADLINE		= $(BREW_DIR)/opt/readline/lib

FLAGS = -Wall -Werror -Wextra

INCLUDE_DIRS = -I src/libft -I include -I $(BREW_DIR)/opt/readline/include 

LIB_DIRS = src/libft/libft.a -L$(LIBREADLINE) -lreadline 

OBJ_DIR = obj

OBJ = $(addprefix obj/, $(SRC:%.c=%.o))

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ) 
	@make -C src/libft
	@echo "compiling $<"
	@gcc $(OBJ) $(FLAGS) $(LIB_DIRS) $(INCLUDE_DIRS) -o minishell

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "compiling $<"
	@gcc -c $^ -o $@ $(FLAGS) $(INCLUDE_DIRS)

$(OBJ_DIR):
	@mkdir -p obj

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
