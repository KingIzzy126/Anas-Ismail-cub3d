/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialashqa <ialashqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:03:15 by ismailalash       #+#    #+#             */
/*   Updated: 2025/07/02 11:27:48 by ialashqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(t_point pos, int size, int color, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(pos.x + i, pos.y, color, game);
	i = -1;
	while (++i < size)
		put_pixel(pos.x, pos.y + i, color, game);
	i = -1;
	while (++i < size)
		put_pixel(pos.x + size, pos.y + i, color, game);
	i = -1;
	while (++i < size)
		put_pixel(pos.x + i, pos.y + size, color, game);
}

/**
 * @brief Draws the minimap top left corner of the game window.
 * @note Draws a square on the minimap at the specified position.
*/
void	draw_minimap(t_game *game)
{
	int		tile_size;
	int		x;
	int		y;
	t_point	pos;

	tile_size = 8;
	y = 0;
	while (game->info->map[y])
	{
		x = 0;
		while (game->info->map[y][x])
		{
			if (game->info->map[y][x] == '1')
			{
				pos.x = x * tile_size;
				pos.y = y * tile_size;
				draw_square(pos, tile_size, 0xAAAAAA, game);
			}
			x++;
		}
		y++;
	}
	pos.x = game->player.x / WALL * tile_size;
	pos.y = game->player.y / WALL * tile_size;
	draw_square(pos, tile_size / 2, 0x00FF00, game);
}

void	clear_trail(t_game *game)
{
	int	x;
	int	y;

	y = 0;
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
