# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/04 17:29:36 by mkitano           #+#    #+#              #
#    Updated: 2026/06/07 18:43:52 by namatias         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                       FLAGS AND VARIABLES TO COMPILE                         #
################################################################################

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR =		./src/
OBJ_DIR =		./obj/
INCLUDE_DIR =	./include/
LIB_DIR =		./lib/libftx/
MLX_DIR =		./lib/mlx42/
MLX_BUILD =		$(MLX_DIR)/build/

SRC_FILES = main.c \
			./parser/parser_args.c \
			./parser/parser_file.c \
			./parser/parser_utils.c \
			./parser/parser_texture.c

FILES_O = $(SRC_FILES:.c=.o)

OBJS = $(addprefix $(OBJ_DIR), $(FILES_O))
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
ARGS = ./maps/basic_map.cub

################################################################################
#                   	          LIBRARIES        		                       #
################################################################################

LIBFT = $(LIB_DIR)libft.a
IFLAGS = -I$(LIB_DIR)include
LDFLAGS = -L $(LIB_DIR) -L $(MLX_BUILD)
LDLIBS = -lft -lmlx42 -lglfw -lpng16 -ldl -pthread -lm

MLX_LIB = $(MLX_BUILD)libmlx42.a

INCLUDES = -I $(INCLUDE_DIR) -I $(LIB_DIR)include -I $(MLX_DIR)include

################################################################################
#                                   COLORS                                     #
################################################################################

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

################################################################################
#                          		   FUNCTIONS	                               #
################################################################################

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "[\033[0;32mOK\033[0m] $(NAME) COMPILED!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "[\033[0;32mOK\033[0m] COMPILED $<"

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR) --silent

$(MLX_LIB):
	@mkdir -p $(MLX_BUILD)
	@cd $(MLX_BUILD) && cmake .. >/dev/null
	@+cmake --build $(MLX_BUILD) >/dev/null

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR) --silent
	@rm -rf $(MLX_BUILD)
	@echo "[\033[0;32mOK\033[0m] FILES CLEAR!"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIB_DIR) --silent
	@echo "[\033[0;32mOK\033[0m] ALL CLEAR!"

re: fclean all

val: all
	valgrind -q --suppressions=mlx.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME) $(ARGS)

.PHONY: all clean fclean re val
