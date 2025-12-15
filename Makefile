# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/22 21:22:21 by wael              #+#    #+#              #
#    Updated: 2025/12/15 22:47:36 by wchatoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		=	fdf

# Compiler and flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3
RM			=	rm -f

# Directories
SRC_DIR			=	src
OBJ_DIR			=	obj
INC_DIR			=	include
LIBFT_DIR		=	$(INC_DIR)/42-libft
MLX_DIR			=	minilibx-linux

# Libraries
LIBFT		=	$(LIBFT_DIR)/libft.a
MLX			=	$(MLX_DIR)/libmlx.a

# Source files
SRCS		=	main.c \
				parse.c \
				parse2.c \
				draw.c \
				draw2.c \
				utils.c \
				mlx_init.c \
				transform.c \
				color.c \
				hooks.c

# Object files
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include flags
INCLUDES	=	-I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Linker flags for Linux
LDFLAGS		=	-L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all:		$(MLX) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
			@echo "Compiled: $<"

$(LIBFT):
			tar -xzf minilibx-linux.tgz
			@echo "Building libft..."
			@make -C $(LIBFT_DIR) --no-print-directory

$(MLX):
			@echo "Building minilibx..."
			@make -C $(MLX_DIR) --no-print-directory

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
			@$(CC) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)
			@echo "✓ $(NAME) created successfully!"

clean:
			@make clean -C $(LIBFT_DIR) --no-print-directory
			@make clean -C $(MLX_DIR) --no-print-directory 2>/dev/null || true
			@$(RM) -r $(OBJ_DIR)
			@echo "✗ Object files removed"

fclean:		clean
			@make fclean -C $(LIBFT_DIR) --no-print-directory
			@$(RM) $(NAME)
			@echo "✗ $(NAME) removed"

re:			fclean all

norm:
			@norminette $(SRC_DIR) $(INC_DIR)/fdf.h

.PHONY:		all clean fclean re norm
