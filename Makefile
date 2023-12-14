### VAR ###

NAME = minishell
CC = cc

CFLAGS = -Wall -Wextra -Werror -g -O0

SRCS = srcs/main.c srcs/error.c srcs/init_signal.c
OBJS = $(SRCS:%.c=%.o)
RLDIR = $(shell brew --prefix readline)

LIBFT = libft/libft.a
INPUTRC = ~/.inputrc

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(INPUTRC)
	$(CC) $(CFLAGS) -lft -Llibft -lreadline -L $(RLDIR)/lib -I $(RLDIR)/include -o $(NAME) $(OBJS)

$(LIBFT) :
	$(MAKE) -j3 -C libft

$(INPUTRC) :
	echo 'set echo-control-characters off' > ~/.inputrc

.c.o :
		$(CC) $(CFLAG) -c -I $(RLDIR)/include $< -o $@

clean:
		rm -rf $(OBJS)
		@$(MAKE) -C libft clean

fclean: clean
		rm -rf $(NAME) $(LIBFT)

re: fclean all

.phony: all clean fclean re