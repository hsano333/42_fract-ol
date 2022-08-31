/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 03:01:01 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 12:13:50 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRACT_H
#define FRACT_H

#include <stdbool.h>
#include "mlx_int.h"
#include "mlx.h"
#include "ft_printf.h"
//#include "image_fract.h"

#define W_WIDTH	640
#define W_HEIGHT 480
#define IMAGE_WIDTH 720
#define IMAGE_HEIGHT 540

#define ON_DESTROY 17

#define INTERATION_INIT 100
#define SPEED_THRESHOLD 4
#define MOVING_VALUE	10

#define DIVERSION_COUNT_UP_THORESHOLD 0.075
#define DIVERSION_COUNT_DOWN_THORESHOLD 0.003
#define DIVERSION_COUNT_THORESHOLD 10
#define ON_EXPOSE 14

enum	e_fract{
	INVALID,
	MANDELBROT,
	JULIA,
	BURNING_SHIP,
	KOCH,
	GASKET,
};

enum	s_error{
	NO_ERROR,
	MEMORY_ERROR,
	ARGV_ERROR,
	MLX_INIT_ERROR,
	MLX_WINDOW_ERROR,
};

//typedef double long fract_type;
typedef double fract_type;

typedef struct s_point {
	int	x;
	int	y;
}	t_point;

typedef struct s_ipoint {
	fract_type	r;
	fract_type	i;
}	t_ipoint;

typedef struct s_area {
	int	x_begin;
	int	x_last;
	int	y_begin;
	int	y_last;
}	t_area;

typedef struct s_iarea {
	fract_type	r_begin;
	fract_type	r_last;
	fract_type	i_begin;
	fract_type	i_last;
}	t_iarea;

typedef struct s_image {
	void	*image;
	void	*addr;
	int	endian;
	int	bpp;
	int	sl;
	t_area	edge_area;
}	t_image;


typedef struct s_fract {
	int	fract_set;
	void	*window;
	void	*mlx;
	t_image	image_info;
	t_iarea	i_area;
	t_iarea	i_area_base;
	int	w_width;
	int	w_height;
	int	error;
	int	speed_thoreshold;
	int	iteration_max;
	int	diversion_count;
	int	near_diversion_count;
	int	(*get_image)(void *);
	int	(*calc_color)(int, int , int);
	void	(*init)(void *);
	long	zoom_count;
	int	lock;
	int	update_image_flag;
	int	create_image_flag;
	int	local_endian;
	int	defalut_color;
	fract_type	zoom_ratio;
	t_ipoint	step;
	t_ipoint	c;
	t_point		offset;
}	t_fract;


void	init(int argc, char** argv, t_fract *fract);
int	hook_key(int key, void *p);
int	hook_mouse(int key, int x, int y, void*toto);
int	detect_move(int x, int y, void *p);
void	update_display_area(t_fract *fract, t_point point, float zoom_ratio, t_point offset);
void	set_init_value(t_fract * fract);
int	close_fract(t_fract *fract);
int	unlock(t_fract *fract);

#endif
