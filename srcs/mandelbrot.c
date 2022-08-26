/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:22:23 by hsano             #+#    #+#             */
/*   Updated: 2022/08/26 20:29:53 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "color.h"

int	get_mandelbrot_color(t_fract *fract, t_point w_point)
{
	int color;
	t_ipoint	z;
	int	n;
	fract_type	tmp_r;
	fract_type	sum;
	t_ipoint c;
	int	tmp_flag;
	int	diverse_flag;

	c.r = fract->i_area.r_begin + fract->step.r * w_point.x;
	c.i = fract->i_area.i_begin + fract->step.i * w_point.y;
	z.r = 0;
	z.i = 0;
	tmp_flag = false;

	n = 0;
	//printf("iteration_max:%d, fract->speed_thoreshold:%d, x:%d, y:%d, z.r:%f, z.i:%f \n", fract->iteration_max,fract->speed_thoreshold,w_point.x, w_point.y, fract->step.r, fract->step.i  );
	color = 0;
	diverse_flag = false;
	while (n < fract->iteration_max)
	{
		tmp_r = z.r * z.r - z.i * z.i + c.r;
		z.i = 2 * z.r * z.i + c.i;
		z.r = tmp_r;
		sum = z.i * z.i + z.r + z.r;
		if (sum > fract->speed_thoreshold * 0.7)
			tmp_flag = true;
		if (sum > fract->speed_thoreshold)
		{
			fract->diversion_count++;
			diverse_flag = true;
			break;
			//return (color);
		}
			//break;
		//if ((z.r * z.r + z.i * z.i) > fract->speed_thoreshold)
			//break;
		n++;
	}

	color = fract->calc_color(n, fract->iteration_max, diverse_flag);
	/*
	if (break_flag)
	{

	}
	color = (n * 255)/ fract->iteration_max;
	int flag[10] = {0};
	if (0b11000000 & color)
		flag[0] = (int)color;
	if (0b00111000 & color)
		flag[1] = (int)color;
	if (0b00000111 & color)
		flag[2] = (int)color;
	//printf("color = %d, flag[1]=%d,%d,%d\n",color,  flag[0], flag[1], flag[2]);
	color = (flag[0] << 16) + (flag[1] << 8) + (flag[2]);
	*/
	//color = 255;
	//color = 250;
	//color = n;
	//return (n);
	if (tmp_flag && diverse_flag == false)
		fract->near_diversion_count++;


	//color = (y*255)/h+((((w-x)*255)/w)<<16);
	//color = (255 << 16) + (255 << 8) + 255;
	//if (fract->speed_thoreshold)
	//ft_printf("mandelbrot x:%d, y:%d   width:%d\n", x, y, fract->w_width);
	return (color);
}
