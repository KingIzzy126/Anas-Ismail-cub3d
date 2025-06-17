NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

MLX_DIR = ./mlx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

SRCS = \
	execution/draw.c \
	execution/init.c \
	execution/moves.c \
	execution/player.c \
	execution/raycast.c \
	execution/texture.c \
	execution/utils.c \
	parsings/map_parsing.c \
	parsings/check_allowed_player_zero.c \
	parsings/path_identifier.c \
	parsings/check_valid_comma_colors.c \
	parsings/map_parsing_utils.c \
	parsings/header_parsing.c \
	parsings/color_value.c \
	parsings/check_allowed_spaces.c \
	utils/ft_atoi_modified.c \
	utils/ft_split.c \
	utils/get_next_line.c \
	utils/get_next_line_utils.c \
	utils/ft_strlcpy.c \
	utils/array_utils.c \
	utils/free_string.c \
	utils/ft_strcmp.c \
	utils/ft_strdup.c \
	utils/ft_strjoin.c \
	utils/ft_strlen.c \
	main_mandatory.c \
	cub3D_utils.c

OBJS = $(SRCS:.c=.o)

all: mlx_compiled $(NAME)

mlx_compiled:
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@
	
clean:
	$(RM) $(OBJS)
	$(RM) main_mandatory.o cub3D_utils.o
	$(RM) execution/*.o parsing/*.o utils/*.o

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re mlx_compiled
