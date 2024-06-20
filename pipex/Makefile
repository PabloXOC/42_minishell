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

#compiler
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

#executable
NAME = pipex.a

#files
SRCS = access_files.c aid.c aid2.c cleanup.c command_path.c \
	lists.c pipex_exec_coms.c
OBJS = $(SRCS:.c=.o)

INCLUDES = pipex.h

#rules
all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	@echo "$(YELLOW)$(BOLD)Compiling pipex...$(RESET)"
	@ar rcs $(NAME) $(OBJS)
	@echo "$(CYAN)$(BOLD)Done.$(RESET)"

#$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)$(BOLD)Cleaning objects from pipex...$(RESET)"
	@rm -f $(OBJS)
	@echo "$(GREEN)$(BOLD)Done.$(RESET)"


fclean: clean
	@rm -f $(NAME)

re: fclean all

.DEFAULT_GOAL := all
