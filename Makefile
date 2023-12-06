### VAR ###

NAME = minishell
CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c
OBJS = $(SRCS:%.c=%.o)
RLDIR = $(shell brew --prefix readline)

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) -lreadline -L $(RLDIR)/lib -I $(RLDIR)/include -o $(NAME) $(OBJS)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.phony: all clean fclean re