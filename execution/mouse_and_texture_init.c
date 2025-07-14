/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_and_texture_init.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialashqa <ialashqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:05:21 by ialashqa          #+#    #+#             */
/*   Updated: 2025/07/14 14:02:26 by ialashqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_press(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == TRIGGER)
		game->is_shooting = true;
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == TRIGGER)
		game->is_shooting = false;
	return (0);
}

void	handle_texture_load_error(const char *texture_path, t_game *game)
{
	fprintf(stderr, "E: Failed to load texture path: %s\n", texture_path);
	game->exit_code = EXIT_FAILURE;
	close_window(game);
}

void	init_texture_pointers(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].img = NULL;
		i++;
	}
	i = 0;
	while (i <= 5)
	{
		game->visors[i].img = NULL;
		i++;
	}
	game->gun_normal.img = NULL;
	game->gun_shoot.img = NULL;
}

void	cleanup_textures(t_game *game)
{
	int	i;

	if (!game)
		return ;
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
}
