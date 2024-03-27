#compiler
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

#executable
NAME = libft.a

#files
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
ft_memset.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c \
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
ft_tolower.c ft_toupper.c ft_itoa.c ft_strmapi.c \
ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_printf.c ft_write.c ft_write2.c 

OBJS = $(SRCS:.c=.o)

SRCS_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
ft_lstmap_bonus.c

OBJS_B = $(SRCS_B:.c=.o)

INCLUDES = libft.h ft_printf.h

#rules
all: $(NAME)

$(NAME): $(OBJS) $(OBJS_B) $(INCLUDES)
	ar rcs $(NAME) $(OBJS)
	ar rcs $(NAME) $(OBJS_B)

#$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_B)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJS_B) $(INCLUDES)
	ar rcs $(NAME) $(OBJS_B)

.DEFAULT_GOAL := all
