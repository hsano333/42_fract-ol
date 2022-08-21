/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 03:01:01 by hsano             #+#    #+#             */
/*   Updated: 2022/08/21 12:22:15 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRACT_H
#define FRACT_H

#include <stdbool.h>
#include	"mlx_int.h"
#include	"mlx.h"

#define W_HEIGHT 1024
#define W_WIDTH	768

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

typedef struct s_fract {
	int	fract_set;
	void	*window;
	void	*mlx;
	int	error;
}	t_fract;


void	init(int argc, char** argv, t_fract *fract);
int	hook_key(int key,void *p);
int	hook_mouse(int x,int y,int button,void*toto);
int	detect_move(int x,int y, void *p);


#endif
