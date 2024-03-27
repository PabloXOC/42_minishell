#gcc so_long.c map.c check_map.c MLX42/libmlx42.a libft/libft.a -Iinclude -lglfw -L "/Users/pximenez/.brew/opt/glfw/lib/" -o so_long
#gcc so_long.c map.c check_map.c MLX42/libmlx42.a libft/libft.a -Iinclude -ldl -lglfw -pthread -lm -o so_long

#//= Colors =//#
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

# Compilers
CC = cc
CFLAGS = -g
LIB_DIR = libft/
LIBS = $(LIB_DIR)libft.a
INCLUDES = -I $(LIB_DIR) -I.
SRC_DIR = srcs/

# Files
SRCS = $(SRC_DIR)main.c 
OBJS = $(SRCS:.c=.o)

# Executable name
NAME = minishell

# Rules
all : $(NAME)

$(NAME): $(OBJS) $(LIBS)
	@echo "$(MAGENTA)$(BOLD)Compiling minishell...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIBS)
	@echo "$(CYAN)$(BOLD)Done$(RESET)"

$(LIBS):
	@make -C $(LIB_DIR)

%.o: %.c minishell.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)$(BOLD)Cleaning objects from minishell...$(RESET)"
	@rm -f $(OBJS)
	@echo "$(GREEN)$(BOLD)Done.$(RESET)"
	@make -C $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_DIR) fclean

re : fclean all

.PHONY : all re fclean clean