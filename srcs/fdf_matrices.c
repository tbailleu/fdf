/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrices.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 09:41:53 by tbailleu          #+#    #+#             */
/*   Updated: 2017/12/29 11:57:00 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	apply_matrice(t_matrice *m, t_env *env)
{
	t_point	*p;
	int		x;
	int		y;

	y = 0;
	while (y < env->map->len)
	{
		x = 0;
		while (x < (env->map->lines[y]->len))
		{
			p = env->map->lines[y]->points[x];
			p->x -= env->center.x;
			p->y -= env->center.y;
			p->z = p->x * m->c1 + p->y * m->c2 + p->z * m->c3 + p->s * m->c4;
			p->y = p->x * m->b1 + p->y * m->b2 + p->z * m->b3 + p->s * m->b4;
			p->x = p->x * m->a1 + p->y * m->a2 + p->z * m->a3 + p->s * m->a4;
			p->x += env->center.x;
			p->y += env->center.y;
			x++;
		}
		y++;
	}
}

void	map_translate(t_env *env, double x, double y, double z)
{
	t_matrice *transation_m;

	ft_throw_error(!(transation_m = (t_matrice*)ft_memalloc(sizeof(t_matrice))),
		"malloc(): Not enough memory");
	transation_m->a1 = 1;
	transation_m->b2 = 1;
	transation_m->c3 = 1;
	transation_m->a4 = x;
	transation_m->b4 = y;
	transation_m->c4 = z;
	transation_m->d4 = 1;
	apply_matrice(transation_m, env);
	get_map_center(env);
	free(transation_m);
}

void	map_scale(t_env *env, double scale)
{
	t_matrice *scale_mat;

	ft_throw_error(!(scale_mat = (t_matrice*)ft_memalloc(sizeof(t_matrice))),
		"malloc(): Not enough memory");
	scale_mat->a1 = scale;
	scale_mat->b2 = scale;
	scale_mat->c3 = scale;
	scale_mat->d4 = 1;
	apply_matrice(scale_mat, env);
	free(scale_mat);
}

void	map_rotate(t_env *env, double theta, char axe)
{
	double		ct;
	double		st;
	t_matrice	*rot_mat;

	ft_throw_error(!(rot_mat = (t_matrice*)ft_memalloc(sizeof(t_matrice))),
		"malloc(): Not enough memory");
	ct = cos(theta);
	st = sin(theta);
	rot_mat->a1 = ct;
	rot_mat->b2 = ct;
	rot_mat->c3 = ct;
	rot_mat->d4 = 1;
	(axe == 'x') ? rot_mat->a1 = 1 : 42;
	(axe == 'x') ? rot_mat->b3 = -st : 42;
	(axe == 'x') ? rot_mat->c2 = st : 42;
	(axe == 'y') ? rot_mat->a3 = st : 42;
	(axe == 'y') ? rot_mat->b2 = 1 : 42;
	(axe == 'y') ? rot_mat->c1 = -st : 42;
	(axe == 'z') ? rot_mat->a2 = -st : 42;
	(axe == 'z') ? rot_mat->b1 = st : 42;
	(axe == 'z') ? rot_mat->c3 = 1 : 42;
	apply_matrice(rot_mat, env);
	free(rot_mat);
}
