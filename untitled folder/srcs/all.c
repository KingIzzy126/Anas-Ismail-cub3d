
#ifndef GAME_H
#define GAME_H

# define WIDTH 750
# define HEIGHT 700
# define WALL 40
# define MINIMAP_SCALE 0.2
# define COLLISION_BUFFER 0.5

# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53
# define LEFT 123
# define RIGHT 124

# define PI 3.14159265358979323846

#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct s_game t_game;

typedef struct s_texture
{
    int width;
    int height;
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
} t_texture;

typedef struct s_player
{
    float x;
    float y;
    float angle;

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool left_rotate;
    bool right_rotate;
    t_game *game;
}   t_player;

typedef struct s_game
{
    void *mlx;
    void *win;
    void *img;

    char *data;
    int bpp;
    int size_line;
    int endian;
    int floor_color;
    int ceiling_color;

    char **map;
    t_texture textures[4];
    t_player player;
}   t_game;

typedef struct s_draw
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
    float   prev_x;
    float   prev_y;
	float	dist;
    int     tex;
    float   tex_pos;
} t_draw;

typedef struct s_render
{
    int height;
    int start_y;
    int end;
    float step;
    float tex_y;
    int tex_x;
    int color;
} t_render;

// draw.c 
void put_pixel(int x, int y, int color, t_game *game);
void draw_square(int x, int y, int size, int color, t_game *game);
void draw_map(t_game *game);
void clear_trail(t_game *game);

// init.c
void init_game(t_game *game);
char **get_map(void);
void load_textures(t_game *game);

// moves.c
void	move_up(t_player *player, int speed, float cos_a, float sin_a);
void	move_down(t_player *player, int speed, float cos_a, float sin_a);
void	move_left(t_player *player, int speed, float cos_a, float sin_a);
void	move_right(t_player *player, int speed, float cos_a, float sin_a);

// player.c
void	init_player(t_player *player);
int     key_press(int keycode, t_player *player);
int     key_release(int keycode, t_player *player);
void	rotate_player(t_player *player);
void    move_player(t_player *player);

// raycast.c
int draw_loop(t_game *game);
void render_3d(t_game *game, int i, float dist, int tex, float tex_pos);
void draw_lines(t_player *player, t_game *game, float start_x, int i);
void draw_floor_ceiling(t_game *game, int x, int wall_top, int wall_bottom, int floor_color, int ceiling_color);
void draw_minimap(t_game *game);

// texture.c
void    init_draw(t_draw *draw, t_player *player, float start_x);
void    change_name_function(t_draw *draw);

// utils.c
bool sensor(float px, float py, t_game *game);
bool is_colliding(float x, float y, t_game *game, float player_size);
float distance(float x1, float y1, float x2, float y2, t_game *game);
int	close_window(t_game *game);
size_t	ft_strlen(const char *str);

#endif

#include "../includes/cub3d.h"

void put_pixel(int x, int y, int color, t_game *game) // Draw pixel
{
    int index;

    if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0) // Bounds check
        return;
    index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
    int i;

    i = -1;
    while (++i < size)
        put_pixel(x + i, y, color, game);
    i = -1;
    while (++i < size)
        put_pixel(x, y + i, color, game);
    i = -1;
    while (++i < size)
        put_pixel(x + size, y + i, color, game);
    i = -1;
    while (++i < size)
        put_pixel(x + i, y + size, color, game);
}

void draw_map(t_game *game)
{
    int i;
    int y;
    char **map;
    int color;

    y = 0;
    map = game->map;
    color = 0xFFFFFF;
    while (map[y])
    {
        i = 0;
        while (map[y][i])
        {
            if (map[y][i] == '1')
                draw_square(i * WALL, y * WALL, WALL, color, game);
            i++;
        }
        y++;
    }
}

void clear_trail(t_game *game)
{
    int x;
    int y;

    y= 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            put_pixel(x, y, 0x000000, game);
            x++;
        }
        y++;
    }
}

void init_game(t_game *game)
{
    init_player(&game->player);
    game->player.game = game;
    game->map = get_map();
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Halo Infinite");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    game->ceiling_color = (0 << 16) | (0 << 8) | 0;        // Black: RGB(0, 0, 128)
    game->floor_color = (0 << 16) | (0 << 8) | 128;        // Navy dark blue: RGB(46, 8, 84) 
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    load_textures(game);
}

char **get_map(void)
{
    char **map;
    
    map = malloc(sizeof(char *) * 13);
    map[0] = "111111111111111111";
    map[1] = "100010000000000001";
    map[2] = "100010000000010001";
    map[3] = "100000000000000001";
    map[4] = "100000001110000001";
    map[5] = "100000001110000001";
    map[6] = "100000001110000001";
    map[7] = "100000100000100001";
    map[8] = "101000000000000101";
    map[9] = "100000100000100001";
    map[10] = "100000000000000001";
    map[11] = "111111111111111111";
    map[12] = NULL;
    return (map);
}

void load_textures(t_game *game)
{
    game->textures[0].img = mlx_xpm_file_to_image(game->mlx,
            "textures/hexagonwall.xpm", &game->textures[0].width,
            &game->textures[0].height);
    game->textures[0].data = mlx_get_data_addr(game->textures[0].img,
            &game->textures[0].bpp, &game->textures[0].size_line,
            &game->textures[0].endian);
    game->textures[1].img = mlx_xpm_file_to_image(game->mlx,
            "textures/blackhexagon.xpm", &game->textures[1].width,
            &game->textures[1].height);
    game->textures[1].data = mlx_get_data_addr(game->textures[1].img,
            &game->textures[1].bpp, &game->textures[1].size_line,
            &game->textures[1].endian);
    game->textures[2].img = mlx_xpm_file_to_image(game->mlx,
            "textures/spaceship.xpm", &game->textures[2].width,
            &game->textures[2].height);
    game->textures[2].data = mlx_get_data_addr(game->textures[2].img,
            &game->textures[2].bpp, &game->textures[2].size_line,
            &game->textures[2].endian);
    game->textures[3].img = mlx_xpm_file_to_image(game->mlx,
            "textures/spaceshipdark.xpm", &game->textures[3].width,
            &game->textures[3].height);
    game->textures[3].data = mlx_get_data_addr(game->textures[3].img,
            &game->textures[3].bpp, &game->textures[3].size_line,
            &game->textures[3].endian);
}

int main(void)
{
    t_game  game;

    init_game(&game);

    mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
    mlx_hook(game.win, 17, 1L << 17, close_window, &game); // close window
    
    mlx_loop_hook(game.mlx, draw_loop, &game);

    mlx_loop(game.mlx);

    return 0;
}

void	move_up(t_player *player, int speed, float cos_a, float sin_a)
{
	float new_x;
	float new_y;
	float player_size;

	player_size = COLLISION_BUFFER;
	if (player->key_up)
	{
		new_x = player->x + speed * cos_a;
		new_y = player->y + speed * sin_a;
		if (!is_colliding(new_x, player->y, player->game, player_size))
			player->x = new_x;
		if (!is_colliding(player->x, new_y, player->game, player_size))
			player->y = new_y;
	}
}

void	move_down(t_player *player, int speed, float cos_a, float sin_a)
{
	float new_x;
	float new_y;
	float player_size;

	player_size = COLLISION_BUFFER;
	if (player->key_down)
	{
		new_x = player->x - speed * cos_a;
		new_y = player->y - speed * sin_a;
		if (!is_colliding(new_x, player->y, player->game, player_size))
			player->x = new_x;
		if (!is_colliding(player->x, new_y, player->game, player_size))
			player->y = new_y;
	}
}

void	move_left(t_player *player, int speed, float cos_a, float sin_a)
{
	float new_x;
	float new_y;
	float player_size;

	player_size = COLLISION_BUFFER;
	if (player->key_left)
	{
		new_x = player->x + speed * sin_a;
		new_y = player->y - speed * cos_a;
		if (!is_colliding(new_x, player->y, player->game, player_size))
			player->x = new_x;
		if (!is_colliding(player->x, new_y, player->game, player_size))
			player->y = new_y;
	}
}

void	move_right(t_player *player, int speed, float cos_a, float sin_a)
{
	float new_x;
	float new_y;
	float player_size;

	player_size = COLLISION_BUFFER;
	if (player->key_right)
	{
		new_x = player->x - speed * sin_a;
		new_y = player->y + speed * cos_a;
		if (!is_colliding(new_x, player->y, player->game, player_size))
			player->x = new_x;
		if (!is_colliding(player->x, new_y, player->game, player_size))
			player->y = new_y;
	}
}

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == ESC)
		close_window(player->game);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void	rotate_player(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.03;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

void	move_player(t_player *player)
{
	int		speed;
	float	cos_angle;
	float	sin_angle;

	speed = 3;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	rotate_player(player);
	move_up(player, speed, cos_angle, sin_angle);
	move_down(player, speed, cos_angle, sin_angle);
	move_left(player, speed, cos_angle, sin_angle);
	move_right(player, speed, cos_angle, sin_angle);
}

/** 
 * @brief Shoots a ray from the player and calculates where it hits a wall.
 * @note Minimap scale is to size down in minimap position (top left)
 * @note Calls 3d rendering in the end.
 */
void	draw_lines(t_player *player, t_game *game, float start_x, int i)
{
    t_draw draw;
    
    init_draw(&draw, player, start_x);
	while (!sensor(draw.ray_x, draw.ray_y, game))
	{
		put_pixel(draw.ray_x * MINIMAP_SCALE, draw.ray_y * MINIMAP_SCALE, 0xFF00FF, game);
        draw.prev_x = draw.ray_x;
        draw.prev_y = draw.ray_y;
		draw.ray_x += draw.cos_angle;
		draw.ray_y += draw.sin_angle;
	}
	draw.dist = distance(player->x, player->y, draw.ray_x, draw.ray_y, game);
    change_name_function(&draw);
    render_3d(game, i, draw.dist, draw.tex, draw.tex_pos);
}

/**
 * @brief Renders the 3D vertical projection of the walls and colors the floor and ceiling.
 * @param game Pointer to the game struct (render data).
 * @param i Index of the vertical wall strip being drawn.
 * @param dist Distance from player to wall intersection.
 * 
 * @note Calls draw_floor_ceiling to draw the floor and ceiling.
 */
void render_3d(t_game *game, int i, float dist, int tex, float tex_pos)
{
    t_render render;
    t_texture *t;

    render.height = (WALL / dist) * (WIDTH / 2);
    render.start_y = (HEIGHT - render.height) / 2;
    render.end = render.start_y + render.height;
    draw_floor_ceiling(game, i, render.start_y, render.end,
            game->floor_color, game->ceiling_color);
    t = &game->textures[tex];
    render.step = (float)t->height / render.height;
    render.tex_y = 0;
    render.tex_x = (int)(tex_pos * t->width);
    while (render.start_y < render.end)
    {
        int ty = (int)render.tex_y;
        int index = ty * t->size_line + render.tex_x * (t->bpp / 8);
        render.color = (unsigned char)t->data[index] |
                ((unsigned char)t->data[index + 1] << 8) |
                ((unsigned char)t->data[index + 2] << 16);
        put_pixel(i, render.start_y, render.color, game);
        render.tex_y += render.step;
        render.start_y++;
    }
}

/**
 * @brief Draws the ceiling and floor colors for a vertical column.
 * @param game Pointer to game struct.
 * @param x Column index on screen.
 * @param wall_top Starting pixel of wall on screen (lower bound of ceiling).
 * @param wall_bottom Ending pixel of wall on screen (upper bound of floor).
 * @param floor_color RGB color of floor.
 * @param ceiling_color RGB color of ceiling.
 */
void draw_floor_ceiling(t_game *game, int x, int wall_top, int wall_bottom, int floor_color, int ceiling_color)
{
    int y;

    y = 0;
    while (y < wall_top)
    {
        put_pixel(x, y, ceiling_color, game);
        y++;
    }
    y = wall_bottom;
    while (y < HEIGHT)
    {
        put_pixel(x, y, floor_color, game);
        y++;
    }
}

/**
 * @brief Draws the minimap top left corner of the game window.
 * @note Draws a square on the minimap at the specified position.
*/
void draw_minimap(t_game *game)
{
    int tile_size;
    int x;
    int y;
    
    tile_size = 8; // size of square on minimap
    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == '1')
                draw_square(x * tile_size, y * tile_size, tile_size, 0xAAAAAA, game);
            x++;
        }
        y++;
    }
    // Draw player on minimap
    draw_square(game->player.x / WALL * tile_size, game->player.y / WALL * tile_size, tile_size / 2, 0x00FF00, game);
}

/**
 * @brief Draws the full screen frame including all rays (walls), floor/ceiling, and minimap.
 * @param game Pointer to game struct.
 * @return Always returns 0 (used by mlx_loop_hook).
 * 
 * @note This is the the main game loop; it updates movement, clears
 *       the image, performs raycasting, and displays the result.
 * @note The coded part is responsible for drawing multiple rays with setting 
 *       the FOV and starting angle.
 */
int draw_loop(t_game *game)
{
    float fraction;
    float start_x;
    int i;
    t_player *player;
    
    player = &game->player;
    move_player(player);
    clear_trail(game);

    fraction = PI / 3 / WIDTH;
    start_x = player->angle - PI / 6;
    i = 0;
    while(i < WIDTH)
    {
        draw_lines(player, game, start_x, i);
        start_x += fraction;
        i++;
    }
    draw_minimap(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

void    init_draw(t_draw *draw, t_player *player, float start_x)
{
    draw->cos_angle = cos(start_x);
    draw->sin_angle = sin(start_x);
    draw->ray_x = player->x;
    draw->ray_y = player->y;
    draw->prev_x = draw->ray_x;
    draw->prev_y = draw->ray_y;
}

void    change_name_function(t_draw *draw)
{
    if ((int)(draw->prev_x / WALL) != (int)(draw->ray_x / WALL))
    {
        if (draw->cos_angle < 0)
            draw->tex = 0;
        else
            draw->tex = 1;
        draw->tex_pos = fmodf(draw->prev_y, WALL) / WALL;
    }
    else
    {
         if (draw->sin_angle < 0)
            draw->tex = 2;
         else
            draw->tex = 3;
        draw->tex_pos = fmodf(draw->prev_x, WALL) / WALL;
    }
}

/**
 * @brief Checks if a given point (px, py) is inside a wall or out of bounds.
 * 
 * @param px The x-coordinate of the point to check.
 * @param py The y-coordinate of the point to check.
 * @param game Pointer to the game structure containing the map.
 * @return true If the point is inside a wall or out of bounds.
 * @return false If the point is valid and not inside a wall.
 */
bool sensor(float px, float py, t_game *game)
{
    int x;
    int y;

    x = (int)(px / WALL);
    y = (int)(py / WALL);
    
    if (x < 0 || y < 0 || !game->map[y]) // Check if point is out of bounds
        return (true); // Out of bounds
    if (x >= (int)ft_strlen(game->map[y])) // Check if x exceeds the row length
        return (true); 
    return (game->map[y][x] == '1');
}

/** * @brief Checks all the 4 player corners if it's colliding with a wall.
 * @param x Player's x position.
 * @param y Player's y position.
 * @param game Pointer to the game struct.
 * @param player_size Size of the player (for collision detection).
 * @return true if collision detected, false no collision.
 */

bool is_colliding(float x, float y, t_game *game, float player_size)
{
    if (sensor(x - player_size, y - player_size, game)) // Top-left
        return true; 
    if (sensor(x + player_size, y - player_size, game)) // Top-right
        return true;
    if (sensor(x - player_size, y + player_size, game)) // Bottom-left
        return true;
    if (sensor(x + player_size, y + player_size, game)) // Bottom-right
        return true;
    return false;
}

float distance(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x;
    float delta_y;
    float angle;
    float fix_dist;

    delta_x = x2 - x1;
    delta_y = y2 - y1;
    angle = atan2(delta_y, delta_x) - game->player.angle;
    fix_dist = sqrt(delta_x * delta_x + delta_y * delta_y) * cos(angle);
    return (fix_dist);
}

int	close_window(t_game *game) // Close window
{
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}