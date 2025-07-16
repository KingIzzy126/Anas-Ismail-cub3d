/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialashqa <ialashqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:46:35 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/07/16 13:36:30 by ialashqa         ###   ########.fr       */
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
