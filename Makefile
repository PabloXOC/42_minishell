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
LIBFT_LST_DIR = libft_lst/

LIBS = $(LIB_DIR)libft.a $(LIBFT_LST_DIR)lst_com.a
INCLUDES = -I $(LIB_DIR) -I. -I $(LIBFT_LST_DIR)

LIB_SYS = -I ./include -I /Users/pximenez/.brew/opt/readline/include
LIB_SYS2 = -L /Users/pximenez/.brew/opt/readline/lib -lreadline

SRC_DIR = srcs
READLINE = -lreadline


# Files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/input.c $(SRC_DIR)/commands.c \
	$(SRC_DIR)/write.c $(SRC_DIR)/terminal_appearance.c $(SRC_DIR)/variables.c  \
	$(SRC_DIR)/check_if_save_input.c $(SRC_DIR)/ft_minishell_split.c \
	$(SRC_DIR)/reformat.c $(SRC_DIR)/token_detection.c $(SRC_DIR)/init.c \
	$(SRC_DIR)/terminal_input.c $(SRC_DIR)/terminal_input_utils.c  \
	$(SRC_DIR)/pipes_access_files.c $(SRC_DIR)/pipes_aid.c $(SRC_DIR)/pipes_aid2.c $(SRC_DIR)/pipes_cleanup.c \
	$(SRC_DIR)/pipes_command_path.c $(SRC_DIR)/pipes_exec_coms.c $(SRC_DIR)/general_cleanup.c $(SRC_DIR)/env.c \
	$(SRC_DIR)/signal_handle.c $(SRC_DIR)/cd.c $(SRC_DIR)/unset.c $(SRC_DIR)/export.c $(SRC_DIR)/echo.c \
	$(SRC_DIR)/files.c $(SRC_DIR)/input_2.c $(SRC_DIR)/input_3.c $(SRC_DIR)/exit_codes.c $(SRC_DIR)/remove_slash.c $(SRC_DIR)/commands2.c \
	$(SRC_DIR)/echo2.c $(SRC_DIR)/utils2.c $(SRC_DIR)/pipes_errors_coms.c $(SRC_DIR)/pipes_exec_coms2.c \
	$(SRC_DIR)/variables_utils.c $(SRC_DIR)/variables_utils2.c $(SRC_DIR)/variables2.c \
	$(SRC_DIR)/input_4.c $(SRC_DIR)/reformat_2.c $(SRC_DIR)/terminal_input_utils_2.c 
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
	@make -C $(LIBFT_LST_DIR)

%.o: %.c minishell.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(MAGENTA)$(BOLD)Cleaning objects from minishell...$(RESET)"
	@rm -f $(OBJS)
	@echo "$(CYAN)$(BOLD)Done.$(RESET)"
	@make -C $(LIB_DIR) clean
	@make -C $(LIBFT_LST_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_DIR) fclean
	@make -C $(LIBFT_LST_DIR) fclean

re : fclean all

.PHONY : all re fclean clean