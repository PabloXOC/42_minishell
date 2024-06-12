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
NAME = lst_com.a

#files
SRCS = ft_lstadd_back_com.c ft_lstadd_front_com.c ft_lstclear_com.c \
	ft_lstdelone_com.c ft_lstiter_com.c ft_lstlast_com.c \
	 ft_lstmap_com.c ft_lstnew_com.c ft_lstsize_com.c \

OBJS = $(SRCS:.c=.o)

INCLUDES = lst_com.h

#rules
all: $(NAME)

$(NAME): $(OBJS) $(OBJS_B) $(INCLUDES)
	@echo "$(YELLOW)$(BOLD)Compiling libft...$(RESET)"
	@ar rcs $(NAME) $(OBJS)
	@ar rcs $(NAME) $(OBJS_B)
	@echo "$(CYAN)$(BOLD)Done.$(RESET)"

#$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)$(BOLD)Cleaning objects from libft...$(RESET)"
	@rm -f $(OBJS)
	@rm -f $(OBJS_B)
	@echo "$(GREEN)$(BOLD)Done.$(RESET)"


fclean: clean
	@rm -f $(NAME)

re: fclean all

.DEFAULT_GOAL := all
