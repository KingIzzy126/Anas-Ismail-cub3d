/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:39:44 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/18 19:34:13 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exitmassege(char *error, t_info *info)
{
	if (info->is_hv_err == 1)
		return ;
	printf("Error\n");
	printf("%s", error);
	info->is_hv_err = 1;
}

void	init_info(t_info *info)
{
	info->is_hv_plr = 0;
	info->is_arnd_wall = 0;
	info->x_lngth_mp = -1;
	info->y_lngth_mp = 0;
	info->is_f_m_l = 0;
	info->sz = 50;
	info->is_hv_err = 0;
	info->steps = 0;
	info->ofset = 0;
	info->fd = -2;
	info->number_of_elemnts = 0;
	info->map = NULL;
	info->east_path = NULL;
	info->west_path = NULL;
	info->north_path = NULL;
	info->south_path = NULL;
	info->floor_color.r = -2;
	info->ceiling_color.r = -2;
}

void	free_info(t_info *info)
{
	if (info->map)
		free_array2d(&info->map);
	if (info->east_path)
		info->east_path = free_string(info->east_path);
	if (info->west_path)
		info->west_path = free_string(info->west_path);
	if (info->north_path)
		info->north_path = free_string(info->north_path);
	if (info->south_path)
		info->south_path = free_string(info->south_path);
}

void	check_extension(char *name_map, t_info *info)
{
	char	*comp;
	int		i;
	int		ln;

	i = 4;
	comp = ".cub";
	ln = ft_strlen(name_map);
	if (ln < i)
		exitmassege("Error ending map file extension (.cub)\n", info);
	while (name_map[ln - i])
	{
		if (comp[4 - i] != name_map[ln - i])
			break ;
		i--;
	}
	if (i != 0 || name_map[ln - i])
		exitmassege("Error ending map file extension (.cub)\n", info);
}

int	open_map_fd(char *name_map, t_info *info)
{
	int	fd;

	check_extension(name_map, info);
	if (info->is_hv_err == 1)
	{
		if (info->fd > 0)
			close (info->fd);
		exit(1);
	}
	fd = open(name_map, O_RDONLY);
	info->fd = fd;
	if (fd == -1)
	{
		exitmassege("Error File Open\n", info);
		exit(1);
	}
	return (fd);
}
