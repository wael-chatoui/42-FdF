# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wael <wael@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/22 21:22:21 by wael              #+#    #+#              #
#    Updated: 2025/11/22 22:51:28 by wael             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		=	fdf

# Compiler and flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -f

# Directories
SRC_DIR		=	src
OBJ_DIR		=	obj
INC_DIR		=	include
FT_PRINTF_DIR	=	ft_printf
GNL_DIR		=	get_next_line
MLX_DIR		=	minilibx-linux

# Libraries
FT_PRINTF	=	$(FT_PRINTF_DIR)/libftprintf.a
MLX			=	$(MLX_DIR)/libmlx.a

# Source files
SRCS		=	main.c \
				parse.c \
				draw.c \
				mlx_init.c

# Get_next_line files
GNL_SRCS	=	$(GNL_DIR)/get_next_line.c \
				$(GNL_DIR)/get_next_line_utils.c

# Object files
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
GNL_OBJS	=	$(GNL_SRCS:$(GNL_DIR)/%.c=$(OBJ_DIR)/%.o)
ALL_OBJS	=	$(OBJS) $(GNL_OBJS)

# Include flags
INCLUDES	=	-I$(INC_DIR) -I$(FT_PRINTF_DIR) -I$(GNL_DIR) -I$(MLX_DIR)

# Linker flags
LDFLAGS		=	-L$(FT_PRINTF_DIR) -lftprintf -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

# Colors for output
GREEN		=	\033[0;32m
RED			=	\033[0;31m
RESET		=	\033[0m

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all:		$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
			@echo "$(GREEN)Compiled: $<$(RESET)"

$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
			@echo "$(GREEN)Compiled: $<$(RESET)"

$(FT_PRINTF):
			@echo "$(GREEN)Building ft_printf...$(RESET)"
			@make -C $(FT_PRINTF_DIR) --no-print-directory

$(MLX):
			@echo "$(GREEN)Building minilibx...$(RESET)"
			@make -C $(MLX_DIR) --no-print-directory

$(NAME):	$(FT_PRINTF) $(MLX) $(ALL_OBJS)
			@$(CC) $(ALL_OBJS) $(LDFLAGS) $(FT_PRINTF) $(MLX) -o $(NAME)
			@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

clean:
			@make clean -C $(FT_PRINTF_DIR) --no-print-directory
			@make clean -C $(MLX_DIR) --no-print-directory
			@$(RM) -r $(OBJ_DIR)
			@echo "$(RED)✗ Object files removed$(RESET)"

fclean:		clean
			@make fclean -C $(FT_PRINTF_DIR) --no-print-directory
			@$(RM) $(NAME)
			@echo "$(RED)✗ $(NAME) removed$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re
