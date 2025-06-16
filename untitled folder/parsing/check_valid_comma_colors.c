/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_comma_colors.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:32:29 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/16 20:32:52 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_valid_comma_each_string(int i, char **array2d, t_info *info)
{
	int	j;

	j = 0;
	if (info->is_hv_err == 1)
		return (1);
	while (array2d[i][j])
	{
		if (array2d[i][j] == ',')
		{
			if ((array2d[i][j + 1] && array2d[i][j + 1] == ',')
				|| (!array2d[i][j + 1] && array2d[i + 1] && array2d[i + 1][0]
					&& array2d[i + 1][0] == ','))
			{
				exitmassege("Error parsing colors format (r,g,b).\n", info);
				return (1);
			}
		}
		j++;
	}
	return (0);
}

int	check_valid_comma(char **array2d, t_info *info)
{
	int	i;
	int	len;

	i = 1;
	if (!array2d[i])
		exitmassege("Error parsing colors format (r,g,b).\n", info);
	while (info->is_hv_err == 0 && array2d[i])
	{
		if (i == 1 && array2d[i][0] == ',')
			exitmassege("Error parsing colors format (r,g,b).\n", info);
		else if (!array2d[i + 1])
		{
			len = ft_strlen(array2d[i]);
			if (array2d[i][len - 1] == ',')
				exitmassege("Error parsing colors format (r,g,b).\n", info);
		}
		if (check_valid_comma_each_string(i, array2d, info) == 1)
			return (1);
		i++;
	}
	if (info->is_hv_err == 1)
		return (1);
	return (0);
}
