/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialashqa <ialashqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:41:06 by ismailalash       #+#    #+#             */
/*   Updated: 2025/07/04 17:09:54 by ialashqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player, t_info *info)
{
	player->x = (info->x_plr + 0.5) * WALL;
	player->y = (info->y_plr + 0.5) * WALL;
	if (info->facing_plr == 'N')
		player->angle = PI / 2;
	else if (info->facing_plr == 'S')
		player->angle = 3 * PI / 2;
	else if (info->facing_plr == 'E')
		player->angle = 0;
	else if (info->facing_plr == 'W')
		player->angle = PI;
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
	if (keycode == SPACE)
		player->game->is_shooting = true;
	if (keycode == ESC)
		close_window(player->game);
	if (keycode >= 18 && keycode <= 21)
		player->game->current_visor = keycode - 17;
	if (keycode == 23)
		player->game->current_visor = 5;
	if (keycode == 29)
		player->game->current_visor = 0;
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
	if (keycode == SPACE)
		player->game->is_shooting = false;
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
	if (player->angle < 0)
		player->angle += 2 * PI;
	else if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
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
