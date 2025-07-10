/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialashqa <ialashqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:30:00 by ismailalash       #+#    #+#             */
/*   Updated: 2025/07/10 19:35:41 by ialashqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_draw(t_draw *draw, t_player *player, float start_x)
{
	draw->cos_angle = cos(start_x);
	draw->sin_angle = sin(start_x);
	draw->ray_x = player->x;
	draw->ray_y = player->y;
	draw->prev_x = draw->ray_x;
	draw->prev_y = draw->ray_y;
}

void	set_wall_texture_direction(t_draw *draw)
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

int	get_visor_color(t_texture *t, t_visor_params *vp)
{
	int	visor_x;
	int	visor_y;
	int	index;
	int	color;

	visor_x = (int)(vp->x * vp->scale_x);
	visor_y = (int)(vp->y * vp->scale_y);
	index = visor_y * t->size_line + visor_x * (t->bpp / 8);
	color = *(int *)(t->data + index);
	return (color & 0x00FFFFFF);
}

void	draw_visor_overlay(t_game *game)
{
	t_texture		*t;
	t_visor_params	vp;
	int				color;

	if (game->current_visor == 0)
		return ;
	t = &game->visors[game->current_visor];
	vp.scale_x = (float)t->width / WIDTH;
	vp.scale_y = (float)t->height / HEIGHT;
	vp.y = 0;
	while (vp.y < HEIGHT)
	{
		vp.x = 0;
		while (vp.x < WIDTH)
		{
			color = get_visor_color(t, &vp);
			if (color != 0x000000 && color != 0x010101 && color != 0x000606)
				put_pixel(vp.x, vp.y, color, game);
			vp.x++;
		}
		vp.y++;
	}
}

void	draw_crosshair(t_game *game)
{
	int	mid_x;
	int	mid_y;
	int	length;
	int	color;
	int	i;

	mid_x = WIDTH / 2;
	mid_y = HEIGHT / 2;
	length = 5;
	color = 0xFF0000;
	i = -length;
	while (i <= length)
	{
		put_pixel(mid_x + i, mid_y, color, game);
		i++;
	}
	i = -length;
	while (i <= length)
	{
		put_pixel(mid_x, mid_y + i, color, game);
		i++;
	}
}
