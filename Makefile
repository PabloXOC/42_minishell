# Colors
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

LIB_SYS = -I ./include -I /Users/pximenez/.brew/opt/readline/include
LIB_SYS2 = -L /Users/pximenez/.brew/opt/readline/lib -lreadline

SRC_DIR = srcs/
READLINE = -lreadline

# Files
SRCS = $(SRC_DIR)main.c $(SRC_DIR)input.c $(SRC_DIR)write.c $(SRC_DIR)utils.c
#$(SRC_DIR)main.c $(SRC_DIR)utils.c $(SRC_DIR)input.c $(SRC_DIR)commands.c \
	$(SRC_DIR)write.c $(SRC_DIR)terminal_appearance.c $(SRC_DIR)variables.c $(SRC_DIR)reformat.c \
	$(SRC_DIR)check_if_save_input.c $(SRC_DIR)open_input.c 
OBJS = $(SRCS:.c=.o)

# Executable name
NAME = minishell

# Rules
all : $(NAME)

$(NAME): $(OBJS) $(LIBS)
	@echo "$(MAGENTA)$(BOLD)Compiling minishell...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIB_SYS) $(LIB_SYS2) -o $@ $(OBJS) $(LIBS) $(READLINE)
	@echo "$(CYAN)$(BOLD)Done$(RESET)"

$(LIBS):
	@make -C $(LIB_DIR)

%.o: %.c minishell.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(MAGENTA)$(BOLD)Cleaning objects from minishell...$(RESET)"
	@rm -f $(OBJS)
	@echo "$(CYAN)$(BOLD)Done.$(RESET)"
	@make -C $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_DIR) fclean

re : fclean all

.PHONY : all re fclean clean