/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 09:46:28 by tbailleu          #+#    #+#             */
/*   Updated: 2018/01/29 17:11:55 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_point(t_point point, t_env *env, int color)
{
	int i;

	i = ((int)point.x * 4) + ((int)point.y * env->line_size);
	env->pixel_img[i] = color;
	env->pixel_img[i + 1] = color >> 8;
	env->pixel_img[i + 2] = color >> 16;
}

void	draw_line(t_point p1, t_point p2, t_env *env)
{
	double  dx;
	double  dy;
	int     i;

	if (!is_on_screen(p1) && !is_on_screen(p2))
		return ;
	i = BLOC_SIZE * fmax(fabs(p1.x - p2.x), fabs(p1.y - p2.y)) / 5;
	i = i ? i : 1;
	dx = (p1.x - p2.x) / i;
	dy = (p1.y - p2.y) / i;
	while (i)
	{
		i--;
		(is_on_screen(p1) == 1) ? draw_point(p1, env, get_color(p1, p2)) : 42;
		p1.x += dx;
		p1.y += dy;
	}
}

void	draw_map(t_env *env)
{
	t_point	point1;
	int		x;
	int		y;

	y = 0;
	while (y < env->map->len)
	{
		x = 0;
		while (x < env->map->lines[y]->len)
		{
			point1 = (*env->map->lines[y]->points[x]);
			if ((x + 1) < env->map->lines[y]->len &&
				env->map->lines[y]->points[x + 1])
				draw_line(point1, (*env->map->lines[y]->points[x + 1]), env);
			if ((y + 1) < env->map->len &&
				env->map->lines[y + 1] &&
				(x + 1) <= env->map->lines[y + 1]->len &&
				env->map->lines[y + 1]->points[x])
				draw_line(point1, (*env->map->lines[y + 1]->points[x]), env);
			x++;
		}
		y++;
	}
}

int		print_frame(t_env *env)
{
	draw_map(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, -50, -50);
	bzero(env->pixel_img, (WIN_HEIGHT + PAD_TOP) * env->line_size);
	return (0);
}
