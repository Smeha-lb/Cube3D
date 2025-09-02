NAME		:= cub3D
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror

MLX_DIR	:= minilibx-linux
MLX_LIB	:= $(MLX_DIR)/libmlx.a
MLX_INC	:= -I$(MLX_DIR)
MLX_LDFLAGS	:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

INCS_DIR	:= includes
SRC_DIR		:= src
OBJ_DIR		:= obj

INCS		:= -I$(INCS_DIR) $(MLX_INC)

SRCS		:= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/app_init.c \
	$(SRC_DIR)/app_hooks.c \
	$(SRC_DIR)/app_render.c \
	$(SRC_DIR)/app_cleanup.c \
	$(SRC_DIR)/utils_str.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/parser_utils.c \
	$(SRC_DIR)/map_validation.c \
	$(SRC_DIR)/textures.c \
	$(SRC_DIR)/player.c \
	$(SRC_DIR)/raycast.c \
	$(SRC_DIR)/minimap.c \
	$(SRC_DIR)/doors.c \
	$(SRC_DIR)/mouse.c \
	$(SRC_DIR)/sprites.c

OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LDFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_DIR) fclean || true

re: fclean all

.PHONY: all clean fclean re
