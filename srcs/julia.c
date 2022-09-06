/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:30:26 by hsano             #+#    #+#             */
/*   Updated: 2022/09/06 09:20:52 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "color.h"
#include "image.h"

static int	calc(t_fract *fract, t_point w_point, \
		int *diverse_flag, int *tmp_flag)
{
	int				n;
	t_ipoint		z;
	t_fract_type	tmp_r;
	t_fract_type	sum;

	z.r = fract->i_area.r_begin + fract->step.r * w_point.x;
	z.i = fract->i_area.i_begin + fract->step.i * w_point.y;
	n = 0;
	while (n++ < fract->iteration_max)
	{
		tmp_r = z.r * z.r - z.i * z.i + fract->c.r;
		z.i = 2 * z.r * z.i + fract->c.i;
		z.r = tmp_r;
		sum = z.r * z.r + z.i * z.i;
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

static int	get_julia_color(t_fract *fract, t_point w_point)
{
	int		color;
	int		n;
	int		tmp_flag;
	int		diverse_flag;

	n = 0;
	color = 0;
	diverse_flag = false;
	tmp_flag = false;
	n = calc(fract, w_point, &diverse_flag, &tmp_flag);
	if (tmp_flag && diverse_flag == false)
		fract->near_diversion_count++;
	color = fract->calc_color(n, fract->iteration_max, diverse_flag);
	return (color);
}

int	get_julia_image(t_fract *fract)
{
	loop_xy(fract, get_julia_color);
	return (true);
}

void	init_julia(t_fract *fract)
{
	fract->fract_set = JULIA;
	fract->get_image = (int (*)())get_julia_image;
	fract->i_area.r_begin = -1.85;
	fract->i_area.r_last = 1.85;
	fract->i_area.i_begin = -1.6;
	fract->i_area.i_last = 1.6;
	fract->iteration_max = INTERATION_INIT;
	fract->calc_color = (int (*)())calc_color7;
	fract->defalut_color = ((255 << 16) + (255 << 8) + 255);
	fract->reverse_y = false;
}
