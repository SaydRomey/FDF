# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/19 21:05:52 by cdumais           #+#    #+#              #
#    Updated: 2024/02/05 14:13:20 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# --------------------------------- VARIABLES -------------------------------- #
# **************************************************************************** #
NAME		:= fdf
MAP_PATH	:= maps/42.fdf

INC_DIR		:= inc
SRC_DIR		:= src
OBJ_DIR		:= obj

LIBFT_DIR	:= libft
LIBFT_INC	:= $(LIBFT_DIR)/$(INC_DIR)
LIBFT_HDR	:= $(LIBFT_INC)/libft.h
LIBFT_SRCS	:= $(wildcard $(LIBFT_DIR)/$(SRC_DIR)/*.c)
LIBFT		:= $(LIBFT_DIR)/libft.a

ifeq ($(shell uname), Linux)
	CLEANUP_SRC = cleanup_linux
	MLX_DIR = minilibx/minilibx_linux
	L_FLAGS = -L$(MLX_DIR) -lmlx -lbsd -lXext -lX11 -lm

else ifeq ($(shell uname), Darwin)
	CLEANUP_SRC = cleanup_mac
	MLX_DIR = minilibx/minilibx_macos
	L_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	$(error Unsupported operating system: $(UNAME))
endif

MLX			= $(MLX_DIR)/libmlx.a

COMPILE		:= gcc
C_FLAGS		:= -Wall -Wextra -Werror

REMOVE		:= rm -rf
NPD			:= --no-print-directory
VOID		:= /dev/null

HEADERS 	:= -I$(INC_DIR) -I$(LIBFT_INC) -I$(MLX_DIR)

# **************************************************************************** #
# --------------------------------- C FILES ---------------------------------- #
# **************************************************************************** #
SRC :=			main								draw					   \
				map									draw_utils				   \
				hooks								transform				   \
				utils								$(CLEANUP_SRC)

# **************************************************************************** #
# --------------------------------- HEADERS ---------------------------------- #
# **************************************************************************** #
INC	:=			fdf															   \
				fdf_utils													   \
				key_linux													   \
				key_macos
# **************************************************************************** #
INCS        :=  $(addprefix $(INC_DIR)/, $(addsuffix .h, $(INC)))
SRCS		:=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))
OBJS		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# **************************************************************************** #
# --------------------------------- ALL FILES -------------------------------- #
# **************************************************************************** #
# INCS		:=	$(wildcard $(INC_DIR)/*.h)
# SRCS		:=	$(wildcard $(SRC_DIR)/*.c)
# OBJS		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# **************************************************************************** #
# ---------------------------------- RULES ----------------------------------- #
# **************************************************************************** #
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(INCS) $(MLX)
	@echo "$(BOLD)$(PURPLE)$(NAME)$(RESET)$(GREEN) created$(RESET)"
	@echo "$(GREEN)$$TITLE$(RESET)"
	@echo "Compiled for $(ITALIC)$(BOLD)$(PURPLE)$(USER)$(RESET) \
		$(CYAN)$(TIME)$(RESET)\n"
	@$(COMPILE) $(C_FLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(L_FLAGS) -o $@
	@echo "type '$(ORANGE)make run$(RESET)' for an example"

$(LIBFT): $(LIBFT_SRCS) $(LIBFT_HDR)
	@make -C $(LIBFT_DIR) $(NPD)

$(MLX):
	@make -C $(MLX_DIR) > $(VOID) 2>&1 || \
		(echo "$(BOLD)$(PURPLE)minilibx$(RESET)$(RED) not found$(RESET)" \
		&& exit 1)
	@echo "$(BOLD)$(PURPLE)minilibx$(RESET)$(GREEN) ready$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@echo "$(CYAN)Compiling...$(ORANGE)\t$(notdir $<)$(RESET)"
	@$(COMPILE) $(C_FLAGS) $(HEADERS) -c $< -o $@
	@printf "$(UP)$(ERASE_LINE)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@if [ -n "$(wildcard $(OBJS)*.o)" ]; then \
		$(REMOVE) $(OBJ_DIR); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)Object files removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)No object files to remove$(RESET)"; \
	fi

fclean: clean
	@if [ -n "$(wildcard $(NAME))" ]; then \
		$(REMOVE) $(NAME); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)Executable removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)No executable to remove$(RESET)"; \
	fi

ffclean: fclean
	@make fclean -C $(LIBFT_DIR) $(NPD)
	@if [ -f $(MLX) ]; then \
		make clean -C $(MLX_DIR) > $(VOID) 2>&1 || \
		(echo "$(BOLD)$(PURPLE)mlx$(RESET)$(RED) clean error$(RESET)" \
		&& exit 1); \
		echo "[$(BOLD)$(PURPLE)mlx$(RESET)] \
		$(GREEN)Object files removed$(RESET)"; \
		echo "[$(BOLD)$(PURPLE)mlx$(RESET)] \
		$(GREEN)Library removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)mlx$(RESET)] \
		$(YELLOW)No object files to remove$(RESET)"; \
		echo "[$(BOLD)$(PURPLE)mlx$(RESET)] \
		$(YELLOW)No library to remove$(RESET)"; \
	fi

re: fclean all

.PHONY: all clean fclean ffclean re

# **************************************************************************** #
run: all
	./$(NAME) $(MAP_PATH)

norm:
	norminette -R CheckForbiddenSourceHeader src/*.c
	norminette -R CheckDefine inc/*.h

pdf:
	@open https://github.com/SaydRomey/FdF/blob/main/info/fdf_en_subject.pdf

# **************************************************************************** #
ROOT_DIR	:=$(notdir $(shell pwd))
TIMESTAMP	:=$(shell date "+%Y%m%d_%H%M%S")
BACKUP_NAME	:=backup_$(ROOT_DIR)_$(TIMESTAMP).zip

backup:
	@if which zip > $(VOID); then \
		zip -r $(BACKUP_NAME) ./*; \
		mv $(BACKUP_NAME) ~/Desktop/; \
	else \
		echo "Please install zip to use the backup feature"; \
	fi

.PHONY: run norm pdf backup

# **************************************************************************** #
# ---------------------------------- LEAKS ----------------------------------- #
# **************************************************************************** #

ifeq ($(shell uname), Linux)
LEAK_TOOL = valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all
else ifeq ($(shell uname), Darwin)
LEAK_TOOL = leaks --atExit --
endif

leaks: C_FLAGS += -g
leaks: all
	$(LEAK_TOOL) ./$(NAME) $(MAP_PATH)

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	--verbose --log-file=valgrind-out.txt ./$(NAME) $(MAP_PATH) \
	&& cat valgrind-out.txt

.PHONY: leaks valgrind

# **************************************************************************** #
# ------------------------------- DECORATIONS -------------------------------- #
# **************************************************************************** #
define TITLE

███████     ██  ███████ 
██          ██  ██      
█████  ███████  █████   
██     ██   ██  ██      
██     ███████  ██      

endef
export TITLE

USER		:=$(shell whoami)
TIME		:=$(shell date "+%H:%M:%S")

title:
	@echo "$(BOLD)$(PURPLE)$(NAME)$(GREEN) created$(RESET)"
	@echo "$(GREEN)$$TITLE$(RESET)"
	@echo "Compiled for $(ITALIC)$(BOLD)$(PURPLE)$(USER)$(RESET) \
		$(CYAN)$(TIME)$(RESET)\n"
# **************************************************************************** #
# ----------------------------------- ANSI ----------------------------------- #
# **************************************************************************** #
# ****** https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797 ******* #

ESC			:= \033

RESET		:= $(ESC)[0m
BOLD		:= $(ESC)[1m
DIM			:= $(ESC)[2m
ITALIC		:= $(ESC)[3m
UNDERLINE	:= $(ESC)[4m
BLINK		:= $(ESC)[5m #no effect on iterm?
INVERT		:= $(ESC)[7m
HIDDEN		:= $(ESC)[8m
STRIKE		:= $(ESC)[9m

# Cursor movement
UP			:= $(ESC)[A
DOWN		:= $(ESC)[B
FORWARD		:= $(ESC)[C
BACK		:= $(ESC)[D
NEXT_LINE	:= $(ESC)[E
PREV_LINE	:= $(ESC)[F
COLUMN		:= $(ESC)[G
TOP_LEFT	:= $(ESC)[1;1H

# Erasing
ERASE_REST	:= $(ESC)[K
ERASE_LINE	:= $(ESC)[2K
ERASE_ALL	:= $(ESC)[2J

# **************************************************************************** #
# ---------------------------------- COLORS ---------------------------------- #
# **************************************************************************** #
# Text
BLACK		:= $(ESC)[30m
RED			:= $(ESC)[91m
GREEN		:= $(ESC)[32m
YELLOW		:= $(ESC)[93m
ORANGE		:= $(ESC)[38;5;208m
BLUE		:= $(ESC)[94m
PURPLE		:= $(ESC)[95m
CYAN		:= $(ESC)[96m
WHITE		:= $(ESC)[37m
GRAY		:= $(ESC)[90m

# Background
BG_BLACK	:= $(ESC)[40m
BG_RED		:= $(ESC)[101m
BG_GREEN	:= $(ESC)[102m
BG_YELLOW	:= $(ESC)[103m
BG_ORANGE	:= $(ESC)[48;5;208m
BG_BLUE		:= $(ESC)[104m
BG_PURPLE	:= $(ESC)[105m
BG_CYAN		:= $(ESC)[106m
BG_WHITE	:= $(ESC)[47m
BG_GRAY		:= $(ESC)[100m

# **************************************************************************** #

# all: $(NAME)

# $(NAME): $(LIBFT) $(OBJS) $(INCS) $(MLX)
# 	@$(COMPILE) $(C_FLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(L_FLAGS) -o $@

# $(LIBFT): $(LIBFT_SRCS) $(LIBFT_HDR)
# 	@make -C $(LIBFT_DIR) $(NPD)

# $(MLX):
# 	@make -C $(MLX_DIR) $(NPD)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
# 	@$(COMPILE) $(C_FLAGS) $(HEADERS) -c $< -o $@

# $(OBJ_DIR):
# 	@mkdir -p $(OBJ_DIR)

# clean:
# 	@$(REMOVE) $(OBJS)
# 	@$(REMOVE) $(OBJ_DIR)

# fclean: clean
# 	@$(REMOVE) $(NAME)
# 	@make clean -C $(MLX_DIR) $(NPD)
# 	@make fclean -C $(LIBFT_DIR) $(NPD)

# re: fclean all

# .PHONY: all clean fclean re
