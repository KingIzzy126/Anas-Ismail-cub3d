NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes
RM = rm -f

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
  LIBX_DIR	+=  minilibx/linux
  MLX_FLAGS	:=  -lXext -lX11
  CPPFLAGS	+=  -D LINUX -Wno-unused-result
else ifeq ($(UNAME), Darwin)
  LIBX_DIR	+=  minilibx/opengl
  MLX_FLAGS	+=  -Lminilibx/opengl -lmlx
  MLX_FLAGS	:=  -framework OpenGL -framework Appkit
  CPPFLAGS	+=  -DSTRINGPUTX11
endif

SRCS = \
	execution/draw.c \
	execution/init.c \
	execution/moves.c \
	execution/player.c \
	execution/raycast.c \
	execution/rifle.c \
	execution/texture.c \
	execution/utils.c \
	parsing/map_parsing.c \
	parsing/check_allowed_player_zero.c \
	parsing/path_identifier.c \
	parsing/check_valid_comma_colors.c \
	parsing/map_parsing_utils.c \
	parsing/header_parsing.c \
	parsing/color_value.c \
	parsing/check_allowed_spaces.c \
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
	@echo "Compiling MiniLibX in: ${LIBX_DIR}"
	@$(MAKE) -C $(LIBX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBX_DIR) -lmlx $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBX_DIR) -c $< -o $@
	
clean:
	$(RM) $(OBJS)
	$(RM) main_mandatory.o cub3D_utils.o
	$(RM) execution/*.o parsing/*.o utils/*.o

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBX_DIR) clean

re: fclean all

.PHONY: all clean fclean re mlx_compiled
