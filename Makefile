### VAR ###

NAME = minishell
CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c
OBJS = $(SRCS:%.c=%.o)
RLDIR = $(shell brew --prefix readline)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -lft -Llibft -lreadline -L $(RLDIR)/lib -I $(RLDIR)/include -o $(NAME) $(OBJS)

$(LIBFT) :
	$(MAKE) -j3 -C libft

clean:
		rm -rf $(OBJS)
		@$(MAKE) -C libft clean

fclean: clean
		rm -rf $(NAME) $(LIBFT)

re: fclean all

.phony: all clean fclean re