/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:22:23 by hsano             #+#    #+#             */
/*   Updated: 2022/08/23 11:24:53 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int	get_mandelbrot_color(t_fract *fract, t_point w_point)
{
	int color;
	t_ipoint	z;
	int	n;
	float	tmp_r;
	t_ipoint c;

	c.r = fract->i_area.r_begin + fract->step.r * w_point.x;
	c.i = fract->i_area.i_begin + fract->step.i * w_point.y;
	z.r = 0;
	z.i = 0;

	n = 0;
	//printf("iteration_max:%d, fract->speed_thoreshold:%d, x:%d, y:%d, z.r:%f, z.i:%f \n", fract->iteration_max,fract->speed_thoreshold,w_point.x, w_point.y, fract->step.r, fract->step.i  );
	while (n < fract->iteration_max)
	{
		tmp_r = z.r * z.r - z.i * z.i + c.r;
		z.i = 2 * z.r * z.i + c.i;
		z.r = tmp_r;
		if (z.r > fract->speed_thoreshold || z.i  > fract->speed_thoreshold )
			break;
		//if ((z.r * z.r + z.i * z.i) > fract->speed_thoreshold)
			//break;
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
