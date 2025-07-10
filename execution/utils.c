/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialashqa <ialashqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:02:20 by ismailalash       #+#    #+#             */
/*   Updated: 2025/07/10 19:35:14 by ialashqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Checks if a given point (px, py) is inside a wall or out of bounds.
 * 
 * @param px The x-coordinate of the point to check.
 * @param py The y-coordinate of the point to check.
 * @param game Pointer to the game structure containing the map.
 * @return true If the point is inside a wall or out of bounds.
 * @return false If the point is valid and not inside a wall.
 */
bool	sensor(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = (int)(px / WALL);
	y = (int)(py / WALL);
	if (x < 0 || y < 0 || !game->info->map[y])
		return (true);
	if (x >= (int)ft_strlen(game->info->map[y]))
		return (true);
	return (game->info->map[y][x] == '1');
}

/** * @brief Checks all the 4 player corners if it's colliding with a wall.
 * @param x Player's x position.
 * @param y Player's y position.
 * @param game Pointer to the game struct.
 * @param player_size Size of the player (for collision detection).
 * @return true if collision detected, false no collision.
 */

bool	is_colliding(float x, float y, t_game *game, float player_size)
{
	if (sensor(x - player_size, y - player_size, game))
		return (true);
	if (sensor(x + player_size, y - player_size, game))
		return (true);
	if (sensor(x - player_size, y + player_size, game))
		return (true);
	if (sensor(x + player_size, y + player_size, game))
		return (true);
	return (false);
}

float	distance(t_points *p, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = p->x2 - p->x1;
	delta_y = p->y2 - p->y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = sqrt(delta_x * delta_x + delta_y * delta_y) * cos(angle);
	return (fix_dist);
}

int	close_window(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	i = 1;
	while (i <= 5)
	{
		if (game->visors[i].img)
			mlx_destroy_image(game->mlx, game->visors[i].img);
		i++;
	}
	if (game->gun_normal.img)
		mlx_destroy_image(game->mlx, game->gun_normal.img);
	if (game->gun_shoot.img)
		mlx_destroy_image(game->mlx, game->gun_shoot.img);
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_window(game->mlx, game->win);
	free_info(game->info);
	exit(EXIT_SUCCESS);
}

size_t	ft_strlen2(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
