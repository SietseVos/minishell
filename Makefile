NAME = minishell

BUILTINS =	cd.c										\
			cd_utils.c									\
			echo.c										\
			env.c										\
			exit.c										\
			export_utils.c								\
			export.c									\
			pwd.c										\
			strings_in_array.c							\
			unset.c										\

ENV =		add_env_node.c								\
			create_env_vars_list.c						\
			env_list_to_array.c							\
			get_variable_node.c							\
			free_env_list.c								\

EXECUTER =	executer.c									\
			save_pid.c									\
			# run_command.c								\
			# make_executable.c							\

LEXER =		lexer.c										\
			in_string.c									\
			check_syntax_error.c						\

PARSER =	parse_cmd.c									\
			parse_file.c								\
			parse_utils.c								\
			parse.c										\
			read_from_str.c								\
			write_to_lst.c								\
			parse_pipe.c								\
			parse_list.c								\
			merge_nodes.c								\

REDIRECTS =	infile.c									\
			outfile.c									\

SIGNALS =	signals.c									\

UTILS =		errors.c									\
			printing.c									\
			freeing.c									\

SRC =	$(addprefix src/builtins/, $(BUILTINS))			\
		$(addprefix src/env_functions/, $(ENV))			\
		$(addprefix src/executer/, $(EXECUTER))			\
		$(addprefix src/lexer/, $(LEXER))				\
		$(addprefix src/parser/, $(PARSER))				\
		$(addprefix src/redirects/, $(REDIRECTS))		\
		$(addprefix src/signals/, $(SIGNALS))			\
		$(addprefix src/utils/, $(UTILS))				\
		src/main.c


BREW_DIR		= $(shell brew --prefix)
LIBREADLINE		= $(BREW_DIR)/opt/readline/lib

FLAGS = -Wall -Werror -Wextra -fsanitize=address -g
#		-fsanitize=address -g

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
