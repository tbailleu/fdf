/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 09:38:27 by tbailleu          #+#    #+#             */
/*   Updated: 2017/12/30 18:52:34 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		parse_line(char *line, int nb_line, t_point ***points, int i)
{
	char	**astr;
	t_point	*point;

	astr = ft_strsplitfree(line, ' ');
	while (astr[i] != '\0')
		i++;
	ft_throw_error(!((*points) = (t_point**)malloc(sizeof(t_point) * i)),
		"malloc(): Not enough memory");
	i = 0;
	while (astr[i] != '\0')
	{
		ft_throw_error(!(point = (t_point*)malloc(sizeof(t_point))),
			"malloc(): Not enough memory");
		point->x = i * BLOC_WIDTH;
		point->y = nb_line * BLOC_HEIGHT;
		point->z = -ft_atoi(astr[i]) * BLOC_DEPTH / 5;
		point->s = 1;
		point->color_z = -point->z / BLOC_DEPTH * 5;
		(*points)[i] = point;
		free(astr[i++]);
	}
	free(astr[i]);
	free(astr);
	return (i);
}

t_map	*parse_map(char **av, int fd)
{
	char	*line;
	int		nb_line;
	t_map	*m;
	t_line	*line_map;
	t_point	**array_points;

	nb_line = 0;
	ft_throw_error(!(m = (t_map*)malloc(sizeof(t_map))) ||
		!(m->lines = (t_line**)malloc(sizeof(t_line) * ft_nbline_file(av[1]))),
		"malloc(): Not enough memory");
	m->len = 0;
	if ((fd = open(av[1], O_RDONLY)) > 0)
	{
		while ((get_next_line(fd, &line)) > 0)
		{
			ft_throw_error(!(line_map = (t_line*)malloc(sizeof(t_line))),
				"malloc(): Not enough memory");
			line_map->len = parse_line(line, nb_line, &array_points, 0);
			line_map->points = array_points;
			m->lines[nb_line] = line_map;
			nb_line++;
		}
		m->len = nb_line;
	}
	return (m);
}

int		maxlength(t_line *a[], int n)
{
	int i;
	int max;
	int maxindex;

	maxindex = 0;
	i = 0;
	max = a[i]->len;
	while (i < n)
	{
		if (a[i]->len > max)
		{
			maxindex = i;
			max = a[i]->len;
		}
		i++;
	}
	return (maxindex);
}

void	get_map_center(t_env *env)
{
	t_point	center;
	int		y_max;
	int		x_max;
	int		xi_max;
	int		yi_max;

	center = env->center;
	yi_max = env->map->len - 1;
	y_max = env->map->lines[yi_max]->len;
	xi_max = maxlength(env->map->lines, yi_max);
	x_max = env->map->lines[xi_max]->len;
	center.x = (env->map->lines[xi_max]->points[x_max - 1]->x +
		env->map->lines[0]->points[0]->x) / 2;
	center.y = (env->map->lines[yi_max]->points[y_max - 1]->y +
		env->map->lines[0]->points[0]->y) / 2;
	env->center = center;
}

void	init_map_transform(t_env *env)
{
	int		width;
	int		height;
	double	scale;

	get_map_center(env);
	width = (WIN_WIDTH + PAD_LEFT) / 2;
	height = (WIN_HEIGHT + PAD_TOP) / 2;
	env->center.x == 0 ? env->center.x = 10 : env->center.x;
	env->mouse_down.s = 0;
	scale = (width - 600) / (env->center.x);
	map_translate(env, width - env->center.x, height - env->center.y, 0);
	map_scale(env, scale);
}
