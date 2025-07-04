/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rifle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialashqa <ialashqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:32:31 by ismailalash       #+#    #+#             */
/*   Updated: 2025/07/02 11:38:36 by ialashqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	toggle_gun_animation(t_game *game)
{
	if (game->is_shooting)
		game->shooting_frame = !game->shooting_frame;
	else
		game->shooting_frame = 0;
}

t_texture	*get_gun_texture(t_game *game)
{
	if (game->is_shooting && game->shooting_frame)
		return (&game->gun_shoot);
	return (&game->gun_normal);
}

void	initialize_gun_render(t_gun_render *render, t_texture *gun)
{
	render->target_w = 500;
	render->target_h = 275;
	render->scale_x = (float)gun->width / render->target_w;
	render->scale_y = (float)gun->height / render->target_h;
	render->x = WIDTH - render->target_w - 0;
	render->y = HEIGHT - render->target_h - 0;
}

void	render_gun(t_game *game, t_texture *gun, t_gun_render *render)
{
	int	i;
	int	j;
	int	index;
	int	color;

	j = 0;
	while (j < render->target_h)
	{
		i = 0;
		while (i < render->target_w)
		{
			index = (int)(j * render->scale_y) * gun->size_line + (int)(i
					* render->scale_x) * (gun->bpp / 8);
			color = *(int *)(gun->data + index);
			if ((color & 0x00FFFFFF) != 0x000000)
				put_pixel(render->x + i, render->y + j, color, game);
			i++;
		}
		j++;
	}
}

void	draw_gun(t_game *game)
{
	t_texture		*gun;
	t_gun_render	render;

	gun = get_gun_texture(game);
	initialize_gun_render(&render, gun);
	render_gun(game, gun, &render);
}
