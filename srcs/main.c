/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 09:22:53 by tbailleu          #+#    #+#             */
/*   Updated: 2018/01/29 16:27:03 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	env_free(t_env *env)
{
	(env->win) ? mlx_destroy_window(env->mlx, env->win) : 42;
	while (env->map->len--)
	{
		while (env->map->lines[env->map->len]->len--)
			(env->map->lines[env->map->len]->points[env->map->lines[env->map->
				len]->len]) ? ft_memdel((void*)&env->map->lines[env->map->len]->
				points[env->map->lines[env->map->len]->len]) : 42;
		if (env->map->lines[env->map->len]->points)
			ft_memdel((void*)&env->map->lines[env->map->len]->points);
		if (env->map->lines[env->map->len])
			ft_memdel((void*)&env->map->lines[env->map->len]);
	}
	(env->map->lines) ? ft_memdel((void*)&env->map->lines) : 42;
	(env->map) ? ft_memdel((void*)&env->map) : 42;
	(env) ? ft_memdel((void*)&env) : 42;
}

int		is_on_screen(t_point point)
{
	return (point.x <= WIN_WIDTH + 100 && point.x > 0 &&
		point.y <= WIN_HEIGHT + 100 && point.y > 0);
}

int		get_color(t_point point1, t_point point2)
{
	int color;
	int z;

	z = (point2.color_z > point1.color_z) ? point2.color_z : point1.color_z;
	color = 0;
	(z <= 0) ? color = 0x3264B8 : 42;
	(z > 0 && z <= 10) ? color = 0x32B864 : 42;
	(z > 10 && z <= 20) ? color = 0x96C896 : 42;
	(z > 20 && z <= 50) ? color = 0xFAFAC8 : 42;
	(z > 50 && z <= 70) ? color = 0x966450 : 42;
	(z > 70) ? color = 0xEFEFEF : 42;
	return (color);
}

int		main(int argc, char **argv)
{
	t_env	*env;
	t_map	*map;

	ft_throw_error(argc != 2, "Usage: fdf filename");
	ft_throw_error(!(env = (t_env *)malloc(sizeof(*env))),
		"malloc(): Not enough memory");
	map = parse_map(argv, 0);
	ft_throw_error(map->len == 0 || map->lines[0]->len == 0,
		"parse_map(): File may be empty or mal-formatted");
	env->map = map;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "42 FDF");
	init_map_transform(env);
	env->img = mlx_new_image(env->mlx, WIN_WIDTH + PAD_LEFT,
		WIN_HEIGHT + PAD_TOP);
	env->pixel_img = mlx_get_data_addr(env->img, &(env->bits_per_pixel),
		&(env->line_size), &(env->endian));
	//mlx_expose_hook(env->win, print_frame, env);
	mlx_hook(env->win, 4, 3, mouse_down_hook, env);
	mlx_hook(env->win, 5, 3, mouse_up_hook, env);
	mlx_hook(env->win, 6, 3, mouse_move_hook, env);
	mlx_hook(env->win, 2, 3, key_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
