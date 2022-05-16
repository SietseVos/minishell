NAME = minishell

BREW_DIR		= $(shell brew --prefix)
LIBREADLINE		= $(BREW_DIR)/opt/readline/lib

testing: testing.c
	gcc testing.c -L$(LIBREADLINE) -l readline -I $(BREW_DIR)/opt/readline/include -o testing