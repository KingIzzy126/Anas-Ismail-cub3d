/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:33:40 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/16 18:45:58 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	len_array2d(char **array2d)
{
	int	len;

	len = 0;
	if (!array2d)
		return (len);
	while (array2d[len])
		len++;
	return (len);
}

void	free_array2d(char ***dst)
{
	int	i;

	if (!*dst)
		return ;
	i = len_array2d(*dst);
	while (i > 0)
	{
		i--;
		if (dst[0][i])
		{
			free(dst[0][i]);
			dst[0][i] = NULL;
		}
	}
	free(*dst);
	*dst = NULL;
}

char	**add_in_array2d(char ***array2d, char *add_str)
{
	int		i;
	int		j;
	int		len;
	char	**new_array2d;

	i = 0;
	j = 0;
	len = len_array2d(*array2d) + 1;
	new_array2d = malloc(sizeof(char *) * (len + 1));
	if (!new_array2d)
		return (NULL);
	while (*array2d && array2d[0][i])
	{
		new_array2d[j++] = ft_strdup(array2d[0][i++]);
	}
	new_array2d[j++] = ft_strdup(add_str);
	new_array2d[j] = NULL;
	free_array2d(array2d);
	return (new_array2d);
}
