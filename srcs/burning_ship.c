/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 20:46:56 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 04:25:33 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fract.h"
#include "color.h"
#include "image.h"

int	get_burning_ship_color(t_fract *fract, t_point w_point)
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
	color = 0;
	diverse_flag = false;
	while (n < fract->iteration_max)
	{
		tmp_r = z.r * z.r - z.i * z.i + c.r;
		z.i = abs(2 * z.r * z.i) + c.i;
		z.r = tmp_r;
		sum = z.i * z.i + z.r + z.r;
		if (sum > fract->speed_thoreshold * 0.7)
			tmp_flag = true;
		if (sum > fract->speed_thoreshold)
		{
			fract->diversion_count++;
			diverse_flag = true;
			break;
		}
		n++;
	}
	color = fract->calc_color(n, fract->iteration_max, diverse_flag);
	if (tmp_flag && diverse_flag == false)
		fract->near_diversion_count++;
	return (color);
}

int	get_burning_ship_image(t_fract *fract)
{
	loop_xy(fract, get_burning_ship_color);
	return (true);
}
