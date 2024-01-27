### VAR ###

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0

PARSER_NAME = parser
PARSER_SRCS = srcs/parser/parse_main.c srcs/parser/parse_utils.c srcs/parser/parse_helper.c srcs/parser/node_constructor.c
PARSER_OBJS = $(PARSER_SRCS:%.c=%.o)
PARSER_HDRS = srcs/parser/parser.h

parser: $(PARSER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -lft -Llibft -lreadline -L $(RLDIR)/lib -I $(RLDIR)/include -I srcs/parser -o $(PARSER_NAME) $(PARSER_OBJS)

srcs/parser/%.o: srcs/parser/%.c $(PARSER_HDRS)
	$(CC) $(CFLAGS) -c -I $(RLDIR)/include -I srcs/parser $< -o $@

ARCH := $(shell uname -m)
ifeq ($(ARCH), x86_64)
	RLDIR = $(shell brew --prefix readline)
else
    RLDIR = /opt/homebrew/opt/readline
endif

SRCS = srcs/main.c srcs/error.c srcs/init_signal.c \
	srcs/lexer/lexer_utils.c srcs/lexer/lexer.c
OBJS = $(SRCS:%.c=%.o)

LIBFT = libft/libft.a
INPUTRC = ~/.inputrc

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(INPUTRC)
	$(CC) $(CFLAGS) -lft -Llibft -lreadline -L $(RLDIR)/lib -I $(RLDIR)/include -o $(NAME) $(OBJS)

$(LIBFT) :
	$(MAKE) -j3 -C libft

.c.o :
		$(CC) $(CFLAG) -c -I $(RLDIR)/include $< -o $@

clean:
		rm -rf $(OBJS)
		@$(MAKE) -C libft clean

fclean: clean
		rm -rf $(NAME) $(LIBFT)

re: fclean all

.phony: all clean fclean re