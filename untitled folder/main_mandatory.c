/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:22:48 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/18 20:52:39 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **arg)
{
	t_info	info;
	int		fd;

	init_info(&info);
	if (ac != 2)
	{
		exitmassege("You Must Have One Map (chose_name.ber)\n", &info);
		exit(1);
	}
	fd = open_map_fd(arg[1], &info);
	map_pars_main(fd, &info);
	// Exit the program if there is an issue
	if (info.is_hv_err == 1)
	{
		if (info.fd > 0)
			close(info.fd);
		free_info(&info);
		return (1);
	}
	// Finish parsing without any issues....
	// Drawing
	// Moving

	
	// Free the data inside the 'info' struct before finishing the program
	free_info(&info);
	return (0);
}
