# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wael <wael@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/22 21:22:21 by wael              #+#    #+#              #
#    Updated: 2025/12/12 18:28:59 by wael             ###   ########.fr        #
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
MLX_DIR			=	MLX42/build
MLX_INC			=	MLX42/include

# Libraries
LIBFT		=	$(LIBFT_DIR)/libft.a
MLX			=	$(MLX_DIR)/libmlx42.a

# Source files
SRCS		=	main.c \
				parse.c \
				draw.c \
				utils.c \
				mlx_init.c

# Object files
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include flags
INCLUDES	=	-I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_INC)

# Linker flags
LDFLAGS		=	-L$(MLX_DIR) -ldl -lglfw -pthread -lm

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all:		$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
			@echo "Compiled: $<"

$(LIBFT):
			@echo "Building libft..."
			@make -C $(LIBFT_DIR) --no-print-directory

$(MLX):
		@echo "Building MLX42..."
		@make -C $(MLX_DIR) --no-print-directory

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
			@$(CC) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)
			@echo "✓ $(NAME) created successfully!"

clean:
			@make clean -C $(LIBFT_DIR) --no-print-directory
			@make clean -C $(MLX_DIR) --no-print-directory
			@$(RM) -r $(OBJ_DIR)
			@echo "✗ Object files removed"

fclean:		clean
			@make fclean -C $(LIBFT_DIR) --no-print-directory
			@$(RM) $(NAME)
			@echo "✗ $(NAME) removed"

re:			fclean all

.PHONY:		all clean fclean re
