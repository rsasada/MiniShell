NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I./includes

#libft
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c\
      ft_isalnum.c ft_isalpha.c ft_isascii.c\
	  ft_isdigit.c ft_isprint.c ft_itoa.c\
      ft_memchr.c ft_memcmp.c ft_memcpy.c\
      ft_memmove.c ft_memset.c ft_putchar_fd.c\
      ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c\
      ft_split.c ft_strchr.c ft_strdup.c\
      ft_striteri.c ft_strjoin.c ft_strlcat.c\
      ft_strlcpy.c ft_strlen.c ft_strmapi.c\
      ft_strncmp.c ft_strnstr.c ft_strrchr.c\
      ft_strtrim.c ft_substr.c ft_tolower.c\
      ft_toupper.c ft_lstadd_back.c  ft_lstadd_front.c \
      ft_lstclear.c  ft_lstdelone.c  ft_lstiter.c \
      ft_lstlast.c  ft_lstmap.c  ft_lstnew.c \
      ft_lstsize.c

#printf
PRINTF_DIR  = ft_printf/
PRINTF = \
              ft_printf.c  format_specifier.c  memory_manager.c \
              number_converter.c  parse_helper.c  parser.c \
              prefix_handler.c  print_chr.c  print_int.c \
              print_ptr.c  printer.c  string_utils.c
PRINTF_SRCS = $(addprefix $(PRINTF_DIR), $(PRINTF))

#gnl
GNL_DIR = gnl/
GNL = get_next_line.c
GNL_SRCS = $(addprefix $(GNL_DIR), $(GNL))


OBJS = $(SRCS:%.c=%.o)
PRINTF_OBJS = $(PRINTF_SRCS:%.c=%.o)
GNL_OBJS = $(GNL_SRCS:%.c=%.o)

all : $(NAME)
# Compile and archive rules
$(NAME): $(OBJS) $(PRINTF_OBJS) $(GNL_OBJS)
	@ar rcs $(NAME) $(OBJS) $(PRINTF_OBJS) $(GNL_OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -g -c $< -o $@

# Clean rules
clean:
	rm -f $(OBJS) $(PRINTF_OBJS) $(GNL_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re