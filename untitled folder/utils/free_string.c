/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:46:35 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/16 17:46:43 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*free_string(char *this_string)
{
	if (!this_string)
		return (NULL);
	free(this_string);
	this_string = NULL;
	return (NULL);
}
