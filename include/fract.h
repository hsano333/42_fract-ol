/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 03:01:01 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 20:42:24 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_H
# define FRACT_H
# define W_WIDTH	640
# define W_HEIGHT 480
# define IMAGE_WIDTH 720
# define IMAGE_HEIGHT 540
# define ON_DESTROY 17
# define INTERATION_INIT 100
# define SPEED_THRESHOLD 4
# define MOVING_VALUE	10
# define DIVERSION_COUNT_UP_THORESHOLD 0.075
# define DIVERSION_COUNT_DOWN_THORESHOLD 0.003
# define DIVERSION_COUNT_THORESHOLD 10
# define ON_EXPOSE 14

# include <stdbool.h>
# include "mlx_int.h"
# include "mlx.h"
# include "ft_printf.h"

enum	e_fract{
	INVALID,
	MANDELBROT,
	JULIA,
	BURNING_SHIP,
	KOCH,
	GASKET,
};

enum	e_error{
	NO_ERROR,
	MEMORY_ERROR,
	ARGV_ERROR,
	MLX_INIT_ERROR,
	MLX_WINDOW_ERROR,
};

typedef double	t_fract_type;
typedef struct s_point {
	int	x;
	int	y;
}	t_point;

typedef struct s_ipoint {
	t_fract_type	r;
	t_fract_type	i;
}	t_ipoint;

typedef struct s_area {
	int	x_begin;
	int	x_last;
	int	y_begin;
	int	y_last;
}	t_area;

typedef struct s_iarea {
	t_fract_type	r_begin;
	t_fract_type	r_last;
	t_fract_type	i_begin;
	t_fract_type	i_last;
}	t_iarea;

typedef struct s_image {
	int		bpp;
	int		sl;
	int		endian;
	void	*image;
	void	*addr;
	t_area	edge_area;
}	t_image;

typedef struct s_fract {
	int				fract_set;
	int				w_width;
	int				w_height;
	int				error;
	int				speed_thoreshold;
	int				iteration_max;
	int				diversion_count;
	int				near_diversion_count;
	int				(*get_image)(void *);
	int				(*calc_color)(int, int, int);
	int				lock;
	int				update_image_flag;
	int				create_image_flag;
	int				local_endian;
	int				defalut_color;
	void			(*init)(void *);
	void			*window;
	void			*mlx;
	long			zoom_count;
	t_point			offset;
	t_image			image_info;
	t_iarea			i_area;
	t_iarea			i_area_base;
	t_ipoint		step;
	t_ipoint		c;
	t_fract_type	zoom_ratio;
}	t_fract;

int			hook_key(int key, void *p);
int			hook_mouse(int key, int x, int y, void*toto);
int			detect_move(int x, int y, void *p);
int			close_fract(t_fract *fract);
void		init(int argc, char **argv, t_fract *fract);
void		set_step(t_fract *fract);
void		update_display_area(t_fract *fract, t_point point \
				, float zoom_ratio, t_point offset);
void		set_init_value(t_fract *fract);
t_ipoint	transform_ri(t_fract *fract, int x, int y);

#endif
