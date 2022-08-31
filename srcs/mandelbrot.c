/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:22:23 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 02:08:01 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "color.h"
#include "image.h"

static int	calc(t_fract *fract, t_ipoint c, int *diverse_flag, int *tmp_flag)
{
	int				n;
	t_ipoint		z;
	t_fract_type	tmp_r;
	t_fract_type	sum;

	z.r = 0;
	z.i = 0;
	n = 0;
	while (n++ < fract->iteration_max)
	{
		tmp_r = z.r * z.r - z.i * z.i - c.r;
		z.i = 2 * z.r * z.i - c.i;
		z.r = tmp_r;
		sum = z.i * z.i + z.r + z.r;
		if (sum > fract->speed_thoreshold * 0.7)
			*tmp_flag = true;
		if (sum > fract->speed_thoreshold)
		{
			fract->diversion_count++;
			*diverse_flag = true;
			break ;
		}
	}
	return (n);
}

static int	get_mandelbrot_color(t_fract *fract, t_point w_point)
{
	int			color;
	int			n;
	int			tmp_flag;
	int			diverse_flag;
	t_ipoint	c;

	c.r = fract->i_area.r_begin + fract->step.r * w_point.x;
	c.i = fract->i_area.i_begin + fract->step.i * w_point.y;
	n = 0;
	color = 0;
	diverse_flag = false;
	tmp_flag = false;
	n = calc(fract, c, &diverse_flag, &tmp_flag);
	if (tmp_flag && diverse_flag == false)
		fract->near_diversion_count++;
	color = fract->calc_color(n, fract->iteration_max, diverse_flag);
	return (color);
}

static int	get_mandelbrot_image(t_fract *fract)
{
	loop_xy(fract, get_mandelbrot_color);
	return (true);
}

void	init_mandelbrot(t_fract *fract)
{
	fract->fract_set = MANDELBROT;
	fract->get_image = (int (*)())get_mandelbrot_image;
	fract->i_area.r_begin = R_START;
	fract->i_area.r_last = R_END;
	fract->i_area.i_begin = I_START;
	fract->i_area.i_last = I_END;
	fract->iteration_max = INTERATION_INIT;
	fract->calc_color = (int (*)())calc_color1;
	fract->defalut_color = ((255 << 16) + (255 << 8) + 255);
}
