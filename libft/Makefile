CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
NAME = libft.a

HDR_LIBFT = libft.h
SRC_LIBFT = standard/ft_atoi.c \
standard/ft_bzero.c \
standard/ft_calloc.c \
standard/ft_isalnum.c \
standard/ft_isalpha.c \
standard/ft_isdigit.c \
standard/ft_islower.c \
standard/ft_isspace.c \
standard/ft_isupper.c \
standard/ft_memcpy.c \
standard/ft_memmove.c \
standard/ft_memset.c \
standard/ft_strcasecmp.c \
standard/ft_strchr.c \
standard/ft_strchrnul.c \
standard/ft_strcmp.c \
standard/ft_strdup.c \
standard/ft_strlcat.c \
standard/ft_strlcpy.c \
standard/ft_strlen.c \
standard/ft_strncasecmp.c \
standard/ft_strncmp.c \
standard/ft_strrchr.c \
standard/ft_toupper.c \
standard/printf/ft_printf.c \
standard/printf/parse.c \
standard/printf/print_alpha.c \
standard/printf/print_dec.c \
standard/printf/print_hex.c \
standard/printf/utils.c \
extra/ft_atoi_base.c \
extra/ft_clamp.c \
extra/ft_gnl.c \
extra/ft_itoa.c \
extra/ft_pow.c \
extra/ft_putstr.c \
extra/ft_split.c \
extra/ft_strjoin.c \
extra/ft_substr.c \
extra/ft_uitoa_base.c \
extra/ft_uitoa.c \
extra/ft_ultoa_base.c \
extra/list/ft_list_add_back.c \
extra/list/ft_list_add_front.c \
extra/list/ft_list_add_sorted.c \
extra/list/ft_list_any.c \
extra/list/ft_list_clear.c \
extra/list/ft_list_count_if.c \
extra/list/ft_list_del_if.c \
extra/list/ft_list_del_one.c \
extra/list/ft_list_find_at.c \
extra/list/ft_list_find_if.c \
extra/list/ft_list_is_sorted.c \
extra/list/ft_list_iter.c \
extra/list/ft_list_last.c \
extra/list/ft_list_map.c \
extra/list/ft_list_new.c \
extra/list/ft_list_size.c \
extra/list/ft_list_sort.c \
extra/list/ft_list_swap_data.c

OBJ_LIBFT = $(SRC_LIBFT:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_LIBFT)
	@ar rcs $@ $^

%.o: %.c $(HDR_LIBFT)
	@$(CC) $(CFLAGS) -I. -o $@ -c $<

clean:
	@rm -f $(OBJ_LIBFT)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
