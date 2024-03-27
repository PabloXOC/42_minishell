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

NAME = minishell

#NAME_BONUS = so_long_bonus

CC = gcc

CFLAGS = 

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

#HEADER = so_long.h $(LIBFT_PATH)/libft.h

MINISHELL = minishell.a

#SO_LONG_BONUS = so_long_bonus.a

SRC_LOC = srcs

LIB = ar rcs

#LIB_SYS = -Iinclude -ldl -lglfw -pthread -lm

#SRCS = codefiles/main.c codefiles/ft_read.c codefiles/ft_makemap.c \
	codefiles/map_fts1.c codefiles/map_fts2.c codefiles/ft_additional.c \
	codefiles/ft_images.c codefiles/ft_keys.c codefiles/ft_additional2.c 

SRCS = $(SRC_LOC)/main.c

OBJS = $(SRCS:.c=.o)

#SRCS_BONUS = srcb/so_long_bonus.c srcb/map_check_bonus.c srcb/map_bonus.c srcb/set_images_bonus.c srcb/player_movement_bonus.c srcb/monster_movement_bonus.c

#OBJS_BONUS = $(SRCS_BONUS:.c=.o)

$(NAME) :	$(OBJS) $(LIBFT) $(MLX)
			@echo "$(MAGENTA)$(BOLD)Compiling minishell...$(RESET)"
			@$(LIB) $(MINISHELL) $(OBJS)
			clang -o minishell $(SRC_LOC)/main.o -lreadline
			@$(CC) $(CFLAGS) $(MINISHELL) $(LIBFT) -o $(NAME)
			@echo "$(CYAN)$(BOLD)Done$(RESET)"

$(OBJS):	$(SRC_LOC)/%.o : $(SRC_LOC)/%.c $(SRC_LOC)/minishell.h
			@$(CC) $(CFLAGS) -c $< -o $@

#$(OBJS_BONUS):	srcb/%.o : srcb/%.c 
#			@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
			@make -s -C $(LIBFT_PATH)
#			@make bonus -s -C $(LIBFT_PATH)

all : $(NAME)

bonus : $(NAME_BONUS)

#$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX)
#			@echo "$(YELLOW)$(BOLD)Compiling so_long_bonus...$(RESET)"
#			@$(LIB) $(SO_LONG_BONUS) $(OBJS_BONUS)
#			@$(CC) $(CFLAGS) $(SO_LONG_BONUS) $(MLX) $(LIBFT) $(LIB_SYS) -o $(NAME_BONUS)
#			@echo "$(CYAN)$(BOLD)Done$(RESET)"

clean:
			@echo "$(RED)$(BOLD)Cleaning objects from minishell...$(RESET)"
			@rm -f $(OBJS) $(OBJS_BONUS)
			@echo "$(GREEN)$(BOLD)Done.$(RESET)"
			@make clean -s -C $(MLX_PATH)
			@make clean -s -C $(LIBFT_PATH)

fclean:
			@echo "$(RED)$(BOLD)Cleaning all files from minishell...$(RESET)"
			@rm -f $(NAME) $(NAME_BONUS) $(OBJS) $(OBJS_BONUS) $(MINISHELL) $(LIBFT)
			@echo "$(GREEN)$(BOLD)Done.$(RESET)"
			@make fclean -s -C $(LIBFT_PATH)

re : fclean all

minishell : all clean

.PHONY : all re fclean clean bonus minishell