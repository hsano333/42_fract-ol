/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 20:46:56 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 19:22:36 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "color.h"
#include "image.h"

static t_fract_type	tmp_abs(t_fract_type a)
{
	if (a >= 0)
		return (a);
	return (0 - a);
}

static int	calc(t_fract *fract, t_ipoint c, int *diverse_flag, int *tmp_flag)
{
	int				n;
	t_ipoint		z;
	t_fract_type	tmp_r;
	t_fract_type	sum;

	z.r = 0;
	z.i = 0;
	n = 0;
	while (n < fract->iteration_max)
	{
		tmp_r = z.r * z.r - z.i * z.i + c.r;
		z.i = tmp_abs(2 * z.r * z.i) + z.i;
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
		n++;
	}
	return (n);
}

int	get_burning_ship_color(t_fract *fract, t_point w_point)
{
	int			color;
	int			n;
	int			tmp_flag;
	int			diverse_flag;
	t_ipoint	c;

	c.r = fract->i_area.r_begin + fract->step.r * w_point.x;
	c.i = fract->i_area.i_begin + fract->step.i * w_point.y;
	tmp_flag = false;
	n = 0;
	diverse_flag = false;
	n = calc(fract, c, &diverse_flag, &tmp_flag);
	if (tmp_flag && diverse_flag == false)
		fract->near_diversion_count++;
	color = fract->calc_color(n, fract->iteration_max, diverse_flag);
	return (color);
}

int	get_burning_ship_image(t_fract *fract)
{
	loop_xy(fract, get_burning_ship_color);
	return (true);
}

void	init_burning_ship(t_fract *fract)
{
	fract->fract_set = BURNING_SHIP;
	fract->get_image = (int (*)())get_burning_ship_image;
	fract->i_area.r_begin = -2.5;
	fract->i_area.r_last = 1.7;
	fract->i_area.i_begin = -1.6;
	fract->i_area.i_last = 1.6;
	fract->iteration_max = INTERATION_INIT;
	fract->calc_color = (int (*)())calc_color6;
	fract->defalut_color = ((255 << 16) + (255 << 8) + 255);
}
