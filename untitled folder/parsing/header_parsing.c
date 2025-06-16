/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:49:13 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/16 20:29:57 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	no_value(char **test_line_map, t_info *info)
{
	if (info->north_path)
	{
		exitmassege("You have filled it out before.\n", info);
		return ;
	}
	info->north_path = path_identifier(test_line_map);
	if (!info->north_path)
	{
		exitmassege("error number of valus1\n", info);
		return ;
	}
	info->number_of_elemnts++;
}

void	so_value(char **test_line_map, t_info *info)
{
	if (info->south_path)
	{
		exitmassege("You have filled it out before.\n", info);
		return ;
	}
	info->south_path = path_identifier(test_line_map);
	if (!info->south_path)
	{
		exitmassege("error number of valus2\n", info);
		return ;
	}
	info->number_of_elemnts++;
}

void	ea_value(char **test_line_map, t_info *info)
{
	if (info->east_path)
	{
		exitmassege("You have filled it out before.\n", info);
		return ;
	}
	info->east_path = path_identifier(test_line_map);
	if (!info->east_path)
	{
		exitmassege("error number of valus3\n", info);
		return ;
	}
	info->number_of_elemnts++;
}

void	we_value(char **test_line_map, t_info *info)
{
	if (info->west_path)
	{
		exitmassege("You have filled it out before.\n", info);
		return ;
	}
	info->west_path = path_identifier(test_line_map);
	if (!info->west_path)
	{
		exitmassege("error number of valus4\n", info);
		return ;
	}
	info->number_of_elemnts++;
}

void	header_parsing(char **test_line_map, t_info *info)
{
	char	**array2d;

	if (info->is_hv_err != 0)
		return ;
	array2d = ft_split(*test_line_map, ' ');
	if (array2d)
	{
		if (!ft_strcmp(array2d[0], "NO"))
			no_value(test_line_map, info);
		else if (!ft_strcmp(array2d[0], "SO"))
			so_value(test_line_map, info);
		else if (!ft_strcmp(array2d[0], "WE"))
			we_value(test_line_map, info);
		else if (!ft_strcmp(array2d[0], "EA"))
			ea_value(test_line_map, info);
		else if (!ft_strcmp(array2d[0], "F"))
			f_value(array2d, info);
		else if (!ft_strcmp(array2d[0], "C"))
			c_value(array2d, info);
		else if (array2d[0])
			exitmassege("is not a valid identifier in header\n", info);
		free_array2d(&array2d);
	}
}
