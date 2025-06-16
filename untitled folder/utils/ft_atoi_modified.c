/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_modified.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:51:48 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/16 17:52:07 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	skip_spaces_and_is_negative(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign[0] = -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = skip_spaces_and_is_negative(str, &sign);
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + (str[i] - '0');
		if (res > 255)
			return (-1);
		i++;
	}
	if (sign == -1 && res != 0)
		return (-1);
	return ((int)res);
}
