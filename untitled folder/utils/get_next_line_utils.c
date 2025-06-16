/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:08:25 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/16 17:45:29 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

size_t	ft_strlen_line(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] && s[i] == '\n')
		i++;
	return (i);
}

char	*ft_strdup_line(char *str, int eof)
{
	char	*dst;
	size_t	i;
	size_t	len;

	i = 0;
	while (str[i] && str[i] != '\n' && eof == 1)
		i++;
	if (!str[i] && eof == 1)
		return (NULL);
	len = ft_strlen_line(str);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup_after_line(char *str)
{
	char	*dst;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str) - ft_strlen_line(str);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	while (str[i])
		dst[j++] = str[i++];
	dst[j] = '\0';
	free_string(str);
	return (dst);
}
