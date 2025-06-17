/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_identifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismailalashqar <ismailalashqar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:29:42 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/06/16 16:55:05 by ismailalash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strlchr(char *str, char lst_char)
{
	int		i;
	char	*dest;

	dest = NULL;
	i = ft_strlen(str);
	while (i > 0 && str[i - 1] == lst_char)
		i--;
	if (i == 0)
		return (NULL);
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, str, i + 1);
	return (dest);
}

char	*path_identifier(char **test_line_map)
{
	char	*path_str;
	int		i;

	i = 0;
	while (test_line_map[0][i] == ' ')
		i++;
	i += 2;
	while (test_line_map[0][i] == ' ')
		i++;
	path_str = ft_strlchr(&test_line_map[0][i], ' ');
	return (path_str);
}
