/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismailalashqar <ismailalashqar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:30:00 by ismailalash       #+#    #+#             */
/*   Updated: 2025/06/18 00:40:03 by ismailalash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    init_draw(t_draw *draw, t_player *player, float start_x)
{
    draw->cos_angle = cos(start_x);
    draw->sin_angle = sin(start_x);
    draw->ray_x = player->x;
    draw->ray_y = player->y;
    draw->prev_x = draw->ray_x;
    draw->prev_y = draw->ray_y;
}

void    set_wall_texture_direction(t_draw *draw)
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

int get_visor_color(t_texture *t, int x, int y, float scale_x, float scale_y)
{
    int visor_x;
    int visor_y;
    int index;
    int color;

    visor_x = (int)(x * scale_x);
    visor_y = (int)(y * scale_y);
    index = visor_y * t->size_line + visor_x * (t->bpp / 8);
    color = *(int *)(t->data + index);

    return color & 0x00FFFFFF; // Normalize color
}

void draw_visor_overlay(t_game *game)
{
    int x;
    int y;
    int color;
    t_texture *t;
    
    if (game->current_visor == 0)
		return;
    t = &game->visors[game->current_visor];
    float scale_x;  
    float scale_y; 
    scale_x = (float)t->width / WIDTH;  // Horizontal scaling factor
    scale_y = (float)t->height / HEIGHT; // Vertical scaling factor
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            color = get_visor_color(t, x, y, scale_x, scale_y);
            if (color != 0x000000 && color != 0x010101 && color != 0x000606) // Skip specific colors
                put_pixel(x, y, color, game);
            x++;
        }
        y++;
    }
}

void draw_crosshair(t_game *game)
{
	int mid_x;
	int mid_y;
	int length;
	int color;
	int i;

	mid_x = WIDTH / 2;
	mid_y = HEIGHT / 2;
	length = 10;
	color = 0xFF0000; // Red

	i = -length;
	while (i <= length)
	{
		put_pixel(mid_x + i, mid_y, color, game);
		i++;
	}
	// Vertical line
	i = -length;
	while (i <= length)
	{
		put_pixel(mid_x, mid_y + i, color, game);
		i++;
	}
}
