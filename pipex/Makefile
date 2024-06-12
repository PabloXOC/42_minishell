# Makefile for pipex

# Compilers
CC = cc
CFLAGS = -g
LIB_DIR = libft/
LIBS = $(LIB_DIR)libft.a
INCLUDES = -I $(LIB_DIR) -I.

# Files
SRCS = access_files.c aid.c aid2.c command_path.c cleanup.c \
	 bonus.c lists.c

OBJS = $(SRCS:.c=.o)

# Executable name
NAME = pipex

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIBS)

$(LIBS):
	make -C $(LIB_DIR)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re