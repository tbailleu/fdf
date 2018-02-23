/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 18:15:29 by tbailleu          #+#    #+#             */
/*   Updated: 2017/12/30 18:39:22 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		key_hook(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
	{
		env_free(env);
		exit(0);
	}
	else if (keycode == KEY_SPACE)
	{
		map_translate(env, (WIN_WIDTH + PAD_LEFT) / 2 - env->center.x,
		(WIN_HEIGHT + PAD_TOP) / 2 - env->center.y, 0);
	}
	else if (keycode == KEY_ZOOM_OUT || keycode == KEY_ZOOM_IN)
		map_scale(env, 1 + (keycode == KEY_ZOOM_OUT ? -1 : 1) * SCALE_ZOOM);
	else if (keycode == KEY_ROTX_U || keycode == KEY_ROTX_D)
		map_rotate(env, (keycode == KEY_ROTX_U ? -1 : 1) * MOVE_ROTX, 'x');
	else if (keycode == KEY_ROTY_U || keycode == KEY_ROTY_D)
		map_rotate(env, (keycode == KEY_ROTY_U ? -1 : 1) * MOVE_ROTY, 'y');
	else if (keycode == KEY_ROTZ_U || keycode == KEY_ROTZ_D)
		map_rotate(env, (keycode == KEY_ROTZ_U ? -1 : 1) * MOVE_ROTZ, 'z');
	print_frame(env);
	return (0);
}

int		mouse_down_hook(int button, int x, int y, t_env *env)
{
	t_point	point;

	env->mouse_down.x = x;
	env->mouse_down.y = y;
	(button == 1) ? env->mouse_down.s = (int)env->mouse_down.s | 1 : 42;
	(button == 3) ? env->mouse_down.s = (int)env->mouse_down.s | 4 : 42;
	if (button == 4 || button == 5)
	{
		point = env->center;
		env->center.x = x + 50;
		env->center.y = y + 50;
		(button == 4) ? map_scale(env, 1 + SCALE_ZOOM) : 42;
		(button == 5) ? map_scale(env, 1 - SCALE_ZOOM) : 42;
		env->center = point;
		print_frame(env);
	}
	return (0);
}

int		mouse_up_hook(int button, int x, int y, t_env *env)
{
	env->mouse_down.x = x;
	env->mouse_down.y = y;
	(button == 1) ? env->mouse_down.s = (int)env->mouse_down.s ^ 1 : 42;
	(button == 3) ? env->mouse_down.s = (int)env->mouse_down.s ^ 4 : 42;
	return (0);
}

int		mouse_move_hook(int x, int y, t_env *env)
{
	t_point	mouse_point;

	mouse_point = env->mouse_down;
	if (((int)mouse_point.s & 1))
	{
		map_translate(env, x - mouse_point.x, y - mouse_point.y, 0);
	}
	if (((int)mouse_point.s & 4))
	{
		map_rotate(env, -(x - mouse_point.x) / 360, 'y');
		map_rotate(env, (y - mouse_point.y) / 360, 'x');
	}
	mouse_point.x = x;
	mouse_point.y = y;
	env->mouse_down = mouse_point;
	print_frame(env);
	return (0);
}
