# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rvan-mee <rvan-mee@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2022/07/05 18:03:46 by rvan-mee      #+#    #+#                  #
#    Updated: 2022/07/08 14:48:24 by svos          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

BUILTINS =	cd.c										\
			cd_utils.c									\
			echo.c										\
			env.c										\
			exit.c										\
			export_add_to_var.c							\
			export_utils.c								\
			export.c									\
			pwd.c										\
			strings_in_array.c							\
			unset.c										\

ENV =		add_env_node.c								\
			create_env_vars_list_utils.c				\
			create_env_vars_list.c						\
			env_list_to_array.c							\
			get_variable_node.c							\
			env_bool_value.c							\

EXECUTER =	executer.c									\
			save_pid.c									\
			execute_path.c								\
			execute_command.c							\
			execute_utils.c								\
			child.c										\
			run_builtins.c								\
			executer_trash.c							\

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
			parse_hdoc.c								\
			parse_ambigu.c								\
			placing_envvar.c							\
			expander.c									\
			expander_strlen.c							\
			expander_strcpy.c							\

REDIRECTS =	infile.c									\
			outfile.c									\
			redirect.c									\
			create_heredoc_file.c						\
			heredoc.c									\
			heredoc_utils.c								\
			directory.c									\

SIGNALS =	signals.c									\

UTILS =		errors.c									\
			printing.c									\
			freeing.c									\
			return.c									\
			more_errors.c								\

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

FLAGS = -Wall -Werror -Wextra
#DEBUG:							-fsanitize=address -fsanitize=leak -g

INCLUDE_DIRS = -I src/libft -I include -I $(BREW_DIR)/opt/readline/include 

LIB_DIRS = src/libft/libft.a -L$(LIBREADLINE) -lreadline 

OBJ_DIR = obj

OBJ = $(addprefix obj/, $(SRC:%.c=%.o))

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ) 
	@make -C src/libft
	@echo "compiling $@"
	@gcc $(OBJ) $(FLAGS) $(LIB_DIRS) $(INCLUDE_DIRS) -o minishell

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "compiling $<"
	@gcc -c $^ -o $@ $(FLAGS) $(INCLUDE_DIRS)

$(OBJ_DIR):
	@mkdir -p obj

clean:
	@echo Cleaning object and temporary files
	@make clean -C src/libft
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo Cleaning executable
	@make fclean -C src/libft
	@rm -f minishell

re: fclean all
