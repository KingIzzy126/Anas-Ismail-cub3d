/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:29:02 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/18 20:50:52 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*els_whl_nxt(char **text_buffer, char *returntext, ssize_t bytesreed,
		t_info *info)
{
	if (bytesreed == 0 && *text_buffer[0])
	{
		returntext = free_string(returntext);
		returntext = ft_strdup_line(*text_buffer, 0);
		*text_buffer = ft_strdup_after_line(*text_buffer);
		if (!*text_buffer[0])
			*text_buffer = free_string(*text_buffer);
		info->is_f_m_l++;
	}
	else
	{
		*text_buffer = free_string(*text_buffer);
		returntext = free_string(returntext);
		return (NULL);
	}
	return (returntext);
}

char	*while_next_line(char **text_buffer, int fd, ssize_t bytesreed,
		t_info *info)
{
	char	*returntext;

	while (bytesreed > 0)
	{
		returntext = malloc(sizeof(char) * (2));
		if (!returntext)
			return (NULL);
		bytesreed = read(fd, returntext, 1);
		if (bytesreed > 0)
		{
			returntext[bytesreed] = '\0';
			*text_buffer = ft_strjoin(*text_buffer, returntext);
			returntext = free_string(returntext);
			returntext = ft_strdup_line(*text_buffer, 1);
			if (returntext)
			{
				*text_buffer = ft_strdup_after_line(*text_buffer);
				break ;
			}
		}
		else
			returntext = els_whl_nxt(text_buffer, returntext, bytesreed, info);
	}
	return (returntext);
}

char	*get_next_line(int fd, t_info *info)
{
	static char	*text_buffer;
	ssize_t		bytesreed;

	if (fd < 0)
		return (NULL);
	if (info->is_hv_err == 1)
	{
		if (text_buffer)
			text_buffer = free_string(text_buffer);
		return (NULL);
	}
	if (!text_buffer)
	{
		text_buffer = malloc(sizeof(char) * (2));
		if (!text_buffer)
			return (NULL);
		text_buffer[0] = '\0';
	}
	bytesreed = 1;
	return (while_next_line(&text_buffer, fd, bytesreed, info));
}
