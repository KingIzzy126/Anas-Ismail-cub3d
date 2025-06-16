/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismailalashqar <ismailalashqar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:46:35 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/06/16 16:55:14 by ismailalash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*free_string(char *this_string)
{
	if (!this_string)
		return (NULL);
	free(this_string);
	this_string = NULL;
	return (NULL);
}
