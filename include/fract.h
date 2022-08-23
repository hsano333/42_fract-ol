/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 03:01:01 by hsano             #+#    #+#             */
/*   Updated: 2022/08/23 16:28:50 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRACT_H
#define FRACT_H

#include <stdbool.h>
#include "mlx_int.h"
#include "mlx.h"
#include "ft_printf.h"
//#include "image_fract.h"

#define W_WIDTH	1024
#define W_HEIGHT 768
#define IMAGE_WIDTH 1280
#define IMAGE_HEIGHT 960

#define INTERATION_MAX 100
#define SPEED_THRESHOLD 5

enum	e_fract{
	MANDELBROT,
	JULIA,
};

enum	s_error{
	NO_ERROR,
	MEMORY_ERROR,
	ARGV_ERROR,
	MLX_INIT_ERROR,
	MLX_WINDOW_ERROR,
};

typedef struct s_point {
	int	x;
	int	y;
}	t_point;

typedef struct s_ipoint {
	float	r;
	float	i;
}	t_ipoint;

typedef struct s_iarea {
	float	r_begin;
	float	r_last;
	float	i_begin;
	float	i_last;
}	t_iarea;

typedef struct s_image {
	void	*image;
	void	*addr;
	int	endian;
	int	bpp;
	int	sl;
}	t_image;

typedef struct s_fract {
	int	fract_set;
	void	*window;
	void	*mlx;
	t_image	image_info;
	t_iarea	i_area;
	int	w_width;
	int	w_height;
	int	error;
	int	speed_thoreshold;
	int	iteration_max;
	int	(*get_color)(void *, t_point);
	t_ipoint	step;
	t_ipoint	c;
}	t_fract;


void	init(int argc, char** argv, t_fract *fract);
int	hook_key(int key, void *p);
int	hook_mouse(int key, int x, int y, void*toto);
int	detect_move(int x, int y, void *p);
void	update_display_area(t_fract *fract, t_point point, float zoom_ratio);


#endif
