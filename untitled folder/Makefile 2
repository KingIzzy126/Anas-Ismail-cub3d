NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

# MLX_DIR = mlx_mac
# MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
SRC_MANDATORY = main_mandatory.c 

# MLX = $(MLX_DIR)/libmlx.a
SRC = parsing/map_parsing.c parsing/check_allowed_player_zero.c parsing/path_identifier.c parsing/check_valid_comma_colors.c \
	parsing/map_parsing_utils.c parsing/header_parsing.c parsing/color_value.c parsing/check_allowed_spaces.c \
	utils/ft_atoi_modified.c utils/ft_split.c utils/get_next_line.c utils/get_next_line_utils.c utils/ft_strlcpy.c \
	utils/array_utils.c utils/free_string.c utils/ft_strcmp.c utils/ft_strdup.c utils/ft_strjoin.c utils/ft_strlen.c \
	cub3D_utils.c

OBJS = $(SRC:.c=.o)
OBJS_MANDATORY = $(SRC_MANDATORY:.c=.o)
# OBJS_BONUS = $(SRC_BONUS:.c=.o)
all: $(NAME)

# $(MLX):
# 		make -C $(MLX_DIR)

$(NAME): $(OBJS) $(OBJS_MANDATORY)
		$(CC) $(OBJS) $(OBJS_MANDATORY) -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_MANDATORY) $(OBJS_BONUS)


fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re 