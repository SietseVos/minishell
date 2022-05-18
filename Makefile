NAME = minishell

BREW_DIR		= $(shell brew --prefix)
LIBREADLINE		= $(BREW_DIR)/opt/readline/lib

all: testing testing2

testing: testing.c
	gcc testing.c -L$(LIBREADLINE) -l readline -I $(BREW_DIR)/opt/readline/include -fsanitize=address -g -o testing

testing2: testing2.c
	gcc testing2.c -L$(LIBREADLINE) -l readline -I $(BREW_DIR)/opt/readline/include -o testing2