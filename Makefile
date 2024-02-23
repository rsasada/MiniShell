### VAR ###

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0


ARCH := $(shell uname -m)
ifeq ($(ARCH), x86_64)
	RLDIR = $(shell brew --prefix readline)
else
    RLDIR = /opt/homebrew/opt/readline
endif

SRCS = srcs/main.c srcs/error.c srcs/init_signal.c \
		srcs/lexer/lexer_utils.c srcs/lexer/lexer.c \
		srcs/parser/parse_main.c srcs/parser/parse_utils.c \
		srcs/parser/parse_helper.c srcs/parser/node_constructor.c \
		srcs/execution/execute_utils.c srcs/execution/execute.c \
		srcs/execution/redirect.c srcs/execution/redirect_utils.c \
		srcs/execution/parse_env.c srcs/utils.c \
		srcs/memory_utils.c srcs/parser/expand.c \
		srcs/env.c srcs/libft_extented/ft_realloc.c

OBJS = $(SRCS:%.c=%.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(INPUTRC)
	$(CC) $(CFLAGS) -lft -Llibft -lreadline -L $(RLDIR)/lib -I $(RLDIR)/include -o $(NAME) $(OBJS)

$(LIBFT) :
	$(MAKE) -j3 -C libft

.c.o :
		$(CC) $(CFLAGS) -c -I $(RLDIR)/include $< -o $@

clean:
		rm -rf $(OBJS)
		@$(MAKE) -C libft clean

fclean: clean
		rm -rf $(NAME) $(LIBFT)

re: fclean all

.phony: all clean fclean re