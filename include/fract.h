/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 03:01:01 by hsano             #+#    #+#             */
/*   Updated: 2022/08/22 18:53:39 by hsano            ###   ########.fr       */
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
	int	w_width;
	int	w_height;
	int	error;
	int	(*get_color)(void *, int , int);
}	t_fract;


void	init(int argc, char** argv, t_fract *fract);
int	hook_key(int key, void *p);
int	hook_mouse(int key, int x, int y, void*toto);
int	detect_move(int x, int y, void *p);


#endif
