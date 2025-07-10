/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialashqa <ialashqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:04:18 by ismailalash       #+#    #+#             */
/*   Updated: 2025/07/10 19:35:53 by ialashqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/** 
 * @brief Shoots a ray from the player and calculates where it hits a wall.
 * @note Minimap scale is to size down in minimap position (top left)
 * @note Calls 3d rendering in the end.
 */
void	draw_lines(t_player *player, t_game *game, float start_x, int i)
{
	t_draw			draw;
	t_render_params	params;
	t_points		p;

	init_draw(&draw, player, start_x);
	while (!sensor(draw.ray_x, draw.ray_y, game))
	{
		put_pixel(draw.ray_x * MINIMAP_SCALE, draw.ray_y * MINIMAP_SCALE,
			0xFF00FF, game);
		draw.prev_x = draw.ray_x;
		draw.prev_y = draw.ray_y;
		draw.ray_x += draw.cos_angle;
		draw.ray_y += draw.sin_angle;
	}
	p.x1 = player->x;
	p.y1 = player->y;
	p.x2 = draw.ray_x;
	p.y2 = draw.ray_y;
	draw.dist = distance(&p, game);
	set_wall_texture_direction(&draw);
	params.col_index = i;
	params.dist = draw.dist;
	params.tex = draw.tex;
	params.tex_pos = draw.tex_pos;
	render_3d(game, &params);
}

/**
 * @brief Renders the 3D vertical projection of the walls/colors + floor&ceiling
 * @param game Pointer to the game struct (render data).
 * @param i Index of the vertical wall strip being drawn.
 * @param dist Distance from player to wall intersection.
 * 
 * @note Calls draw_floor_ceiling to draw the floor and ceiling.
 */
void	render_3d(t_game *game, t_render_params *params)
{
	t_render	render;
	t_texture	*t;
	int			ty;
	int			index;

	render.height = (WALL / params->dist) * (WIDTH / 2);
	render.start_y = (HEIGHT - render.height) / 2;
	render.end = render.start_y + render.height;
	draw_floor_ceiling(game, params->col_index, render.start_y, render.end);
	t = &game->textures[params->tex];
	render.step = (float)t->height / render.height;
	render.tex_y = 0;
	render.tex_x = (int)(params->tex_pos * t->width);
	while (render.start_y < render.end)
	{
		ty = (int)render.tex_y;
		index = ty * t->size_line + render.tex_x * (t->bpp / 8);
		render.color = (unsigned char)t->data[index]
			| ((unsigned char)t->data[index + 1] << 8)
			| ((unsigned char)t->data[index + 2] << 16);
		put_pixel(params->col_index, render.start_y, render.color, game);
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
void	draw_floor_ceiling(t_game *game, int x, int wall_top, int wall_bottom)
{
	int	y;
	int	ceiling_color;
	int	floor_color;

	y = 0;
	ceiling_color = (game->info->ceiling_color.r << 16)
		| (game->info->ceiling_color.g << 8)
		| (game->info->ceiling_color.b);
	floor_color = (game->info->floor_color.r << 16)
		| (game->info->floor_color.g << 8)
		| (game->info->floor_color.b);
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
 * @brief Draws the full screen frame including all rays (walls), floor/ceiling,
	and minimap.
 * @param game Pointer to game struct.
 * @return Always returns 0 (used by mlx_loop_hook).
 * 
 * @note This is the the main game loop; it updates movement, clears
 *       the image, performs raycasting, and displays the result.
 * @note The coded part is responsible for drawing multiple rays with setting 
 *       the FOV and starting angle.
 */
int	draw_loop(t_game *game)
{
	float		fraction;
	float		start_x;
	int			i;
	t_player	*player;

	player = &game->player;
	rotate_with_mouse(player, game);
	move_player(player);
	clear_trail(game);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_lines(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	toggle_gun_animation(game);
	draw_gun(game);
	draw_visor_overlay(game);
	draw_minimap(game);
	draw_crosshair(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
