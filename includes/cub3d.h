/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialashqa <ialashqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:13:59 by ismailalash       #+#    #+#             */
/*   Updated: 2025/07/10 16:56:38 by ialashqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1000
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
# define SPACE 49
# define TRIGGER 1

# define PI 3.14159265358979323846

# include "../minilibx/opengl/mlx.h"
# include "../minilibx/linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_game	t_game;

typedef struct s_texture
{
	int					width;
	int					height;
	void				*img;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_texture;

typedef struct s_player
{
	float				x;
	float				y;
	float				angle;

	bool				key_up;
	bool				key_down;
	bool				key_left;
	bool				key_right;
	bool				left_rotate;
	bool				right_rotate;
	t_game				*game;
}						t_player;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	void				*img;

	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
	int					current_visor;
	int					shooting_frame;
	bool				is_shooting;

	t_texture			gun_normal;
	t_texture			gun_shoot;
	t_texture			textures[4];
	t_texture			visors[6];
	t_player			player;
	struct s_info		*info;
}						t_game;

typedef struct s_draw
{
	float				cos_angle;
	float				sin_angle;
	float				ray_x;
	float				ray_y;
	float				prev_x;
	float				prev_y;
	float				dist;
	int					tex;
	float				tex_pos;
}						t_draw;

typedef struct s_gun_render
{
	int					x;
	int					y;
	float				scale_x;
	float				scale_y;
	int					target_w;
	int					target_h;
}						t_gun_render;

typedef struct s_render
{
	int					height;
	int					start_y;
	int					end;
	float				step;
	float				tex_y;
	int					tex_x;
	int					color;
}						t_render;

typedef struct s_render_params
{
	int					col_index;
	float				dist;
	int					tex;
	float				tex_pos;
}						t_render_params;

typedef struct s_visor_params
{
	int					x;
	int					y;
	float				scale_x;
	float				scale_y;
}						t_visor_params;

typedef struct s_points
{
	float				x1;
	float				y1;
	float				x2;
	float				y2;
}						t_points;

typedef struct s_color_rgb
{
	int					r;
	int					g;
	int					b;
}						t_color_rgb;

typedef struct s_info
{
	int					is_hv_plr;
	int					is_arnd_wall;
	int					x_lngth_mp;
	int					y_lngth_mp;
	int					is_f_m_l;
	int					sz;
	void				*mlx;
	void				*win;
	void				*img;
	int					x_plr;
	int					y_plr;
	char				facing_plr;
	void				*img_plr;
	char				**map;
	void				*img_wl;
	void				*img_wlk;
	int					is_hv_err;
	int					fd;
	int					steps;
	int					ofset;
	int					is_plus;
	int					number_of_elemnts;
	char				*north_path;
	char				*south_path;
	char				*west_path;
	char				*east_path;
	t_color_rgb			floor_color;
	t_color_rgb			ceiling_color;
}						t_info;

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

// draw.c
void					put_pixel(int x, int y, int color, t_game *game);
void					draw_square(t_point pos, int size, int color,
							t_game *game);
void					clear_trail(t_game *game);
void					draw_minimap(t_game *game);

// init.c
void					init_game(t_game *game, t_info *info);
void					load_wall_textures(t_game *game);
void					load_visor_textures(t_game *game);
void					load_gun_textures(t_game *game);
void					load_textures(t_game *game);

// mouse.c
int						mouse_press(int button, int x, int y, t_game *game);
int						mouse_release(int button, int x, int y, t_game *game);

// moves.c
void					move_up(t_player *player, int speed, float cos_a,
							float sin_a);
void					move_down(t_player *player, int speed, float cos_a,
							float sin_a);
void					move_left(t_player *player, int speed, float cos_a,
							float sin_a);
void					move_right(t_player *player, int speed, float cos_a,
							float sin_a);
void					rotate_with_mouse(t_player *player, t_game *game);

// player.c
void					init_player(t_player *player, t_info *info);
int						key_press(int keycode, t_player *player);
int						key_release(int keycode, t_player *player);
void					rotate_player(t_player *player);
void					move_player(t_player *player);

// raycast.c
int						draw_loop(t_game *game);
void					render_3d(t_game *game, t_render_params *params);
void					draw_lines(t_player *player, t_game *game,
							float start_x, int i);
void					draw_floor_ceiling(t_game *game, int x, int wall_top,
							int wall_bottom);

// rifle.c
void					toggle_gun_animation(t_game *game);
t_texture				*get_gun_texture(t_game *game);
void					initialize_gun_render(t_gun_render *render,
							t_texture *gun);
void					render_gun(t_game *game, t_texture *gun,
							t_gun_render *render);
void					draw_gun(t_game *game);

// texture.c
void					init_draw(t_draw *draw, t_player *player,
							float start_x);
void					set_wall_texture_direction(t_draw *draw);
int						get_visor_color(t_texture *t, t_visor_params *vp);
void					draw_visor_overlay(t_game *game);
void					draw_crosshair(t_game *game);

// utils.c
bool					sensor(float px, float py, t_game *game);
bool					is_colliding(float x, float y, t_game *game,
							float player_size);
float					distance(t_points *p, t_game *game);
int						close_window(t_game *game);
size_t					ft_strlen2(const char *str);

//parsing - anas
void					exitmassege(char *error, t_info *info);
void					map_pars_main(int fd, t_info *info);
void					data_map(char *test_line_map, t_info *info);
int						ft_strlen(const char *s);
char					*get_next_line(int fd, t_info *info);
char					*ft_strdup_line(char *str, int eof);
char					*ft_strdup_after_line(char *str);
char					*ft_strjoin(char *s1, char *s2);
char					*free_string(char *this_string);
int						open_map_fd(char *name_map, t_info *info);
void					init_info(t_info *info);
char					**ft_split(char const *s, char c);
char					*ft_strdup(const char *str);
int						ft_atoi(const char *str);
void					header_parsing(char **test_line_map, t_info *info);
void					c_value(char **array2d, t_info *info);
void					f_value(char **array2d, t_info *info);
int						ft_strcmp(const char *s1, const char *s2);
char					**add_in_array2d(char ***array2d, char *add_str);
void					free_array2d(char ***dst);
int						len_array2d(char **array2d);
int						check_zero_player_allowed(t_info *info);
int						check_spaces_allowed(t_info *info);
void					free_info(t_info *info);
void					ft_strlcpy(char *dst, const char *src, size_t dstsize);
char					*path_identifier(char **test_line_map);
int						check_valid_comma(char **array2d, t_info *info);

#endif