/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:30:26 by hsano             #+#    #+#             */
/*   Updated: 2022/08/27 18:32:54 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"

int	get_julia_color(t_fract *fract, t_point w_point)
{
	int color;
	//t_point_image	i_point;
	t_ipoint	z;
	//t_ipoint	tmp;
	//int x = w_point.x;
	//int y = w_point.y;
	//int h = fract->w_height;
	int	n;
	float	tmp_r;

	z.r = fract->i_area.r_begin + fract->step.r * w_point.x;
	z.i = fract->i_area.i_begin + fract->step.i * w_point.y;

	n = 0;
	//printf("iteration_max:%d, fract->speed_thoreshold:%d, x:%d, y:%d, z.r:%f, z.i:%f \n", fract->iteration_max,fract->speed_thoreshold,w_point.x, w_point.y, fract->step.r, fract->step.i  );
	while (n < fract->iteration_max)
	{
		tmp_r = z.r * z.r - z.i * z.i + fract->c.r;
		z.i = 2 * z.r * z.i + fract->c.i;
		z.r = tmp_r;
		if ((z.r * z.r + z.i * z.i) > fract->speed_thoreshold)
			break;
		n++;
	}
	color = (n * 255)/ fract->speed_thoreshold;
	//color = n;
	//return (n);

	//color = (y*255)/h+((((w-x)*255)/w)<<16);
	//color = (255 << 16) + (255 << 8) + 255;
	//if (fract->speed_thoreshold)
	//ft_printf("mandelbrot x:%d, y:%d   width:%d\n", x, y, fract->w_width);
	return (color);
}

int	get_julia_image(t_fract *fract)
{
	loop_xy(fract, get_julia_color);
	return (true);
}
