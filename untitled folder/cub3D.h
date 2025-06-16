/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:07:00 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/18 19:32:07 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_color_rgb
{
	int			r;
	int			g;
	int			b;
}				t_color_rgb;

typedef struct s_info
{
	int			is_hv_plr;
	int			is_arnd_wall;
	int			x_lngth_mp;
	int			y_lngth_mp;
	int			is_f_m_l;
	int			sz;
	void		*mlx;
	void		*win;
	void		*img;
	int			x_plr;
	int			y_plr;
	char		facing_plr;
	void		*img_plr;
	char		**map;
	void		*img_wl;
	void		*img_wlk;
	int			is_hv_err;
	int			fd;
	int			steps;
	int			ofset;
	int			is_plus;
	int			number_of_elemnts;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	t_color_rgb	floor_color;
	t_color_rgb	ceiling_color;
}				t_info;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

void			exitmassege(char *error, t_info *info);
void			map_pars_main(int fd, t_info *info);
void			data_map(char *test_line_map, t_info *info);
int				ft_strlen(const char *s);
char			*get_next_line(int fd, t_info *info);
char			*ft_strdup_line(char *str, int eof);
char			*ft_strdup_after_line(char *str);
char			*ft_strjoin(char *s1, char *s2);
char			*free_string(char *this_string);
int				open_map_fd(char *name_map, t_info *info);
void			init_info(t_info *info);
char			**ft_split(char const *s, char c);
char			*ft_strdup(const char *str);
int				ft_atoi(const char *str);
void			header_parsing(char **test_line_map, t_info *info);
void			c_value(char **array2d, t_info *info);
void			f_value(char **array2d, t_info *info);
int				ft_strcmp(const char *s1, const char *s2);
char			**add_in_array2d(char ***array2d, char *add_str);
void			free_array2d(char ***dst);
int				len_array2d(char **array2d);
int				check_zero_player_allowed(t_info *info);
int				check_spaces_allowed(t_info *info);
void			free_info(t_info *info);
void			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*path_identifier(char **test_line_map);
int				check_valid_comma(char **array2d, t_info *info);
#endif