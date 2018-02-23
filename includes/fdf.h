/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 09:22:48 by tbailleu          #+#    #+#             */
/*   Updated: 2017/12/29 11:56:23 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include "../libft/includes/libft.h"

# define PAD_TOP 100
# define PAD_LEFT 100
# define BLOC_WIDTH 20
# define BLOC_HEIGHT 20
# define BLOC_DEPTH 20

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

/*
**	Transform scale
*/
# define SCALE_ZOOM 0.1

# define MOVE_ROTX (M_PI / 64)
# define MOVE_ROTY (M_PI / 64)
# define MOVE_ROTZ (M_PI / 64)

/*
**	Key code
*/
# define KEY_ESC 53
# define KEY_SPACE 49

# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78

# define KEY_ROTX_U 86
# define KEY_ROTX_D 83
# define KEY_ROTY_U 87
# define KEY_ROTY_D 84
# define KEY_ROTZ_U 88
# define KEY_ROTZ_D 85

typedef struct	s_point {
	double	x;
	double	y;
	double	z;
	double	s;
	int		color_z;
}				t_point;

typedef struct	s_line {
	t_point	**points;
	int		len;
}				t_line;

typedef struct	s_map {
	t_line	**lines;
	int		len;
}				t_map;

typedef struct	s_env {
	void	*mlx;
	void	*win;
	t_point	mouse_down;
	t_map	*map;
	t_point	center;
	void	*img;
	char	*pixel_img;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}				t_env;

typedef struct	s_matrice {
	double a1;
	double a2;
	double a3;
	double a4;
	double b1;
	double b2;
	double b3;
	double b4;
	double c1;
	double c2;
	double c3;
	double c4;
	double d1;
	double d2;
	double d3;
	double d4;
}				t_matrice;

int				key_hook(int keycode, t_env *env);
int				mouse_down_hook(int button, int x, int y, t_env *env);
int				mouse_up_hook(int button, int x, int y, t_env *env);
int				mouse_move_hook(int x, int y, t_env *env);

void			env_free(t_env *env);
int				is_on_screen(t_point point);
int				get_color(t_point point1, t_point point2);

int				parse_line(char *line, int nb_line, t_point ***points, int i);
t_map			*parse_map(char **av, int fd);
int				maxlength(t_line *a[], int n);
void			get_map_center(t_env *env);
void			init_map_transform(t_env *env);

void			apply_matrice(t_matrice *m, t_env *env);
void			map_translate(t_env *env, double x, double y, double z);
void			map_scale(t_env *env, double scale);
void			map_rotate(t_env *env, double theta, char axe);

void			draw_point(t_point point, t_env *env, int color);
void			draw_line(t_point p1, t_point p2, t_env *env);
void			draw_map(t_env *env);
int				print_frame(t_env *env);

#endif
