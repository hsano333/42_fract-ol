/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 05:38:17 by hsano             #+#    #+#             */
/*   Updated: 2022/09/06 07:14:57 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"
#include <float.h>
#include <errno.h>

int	close_fract(t_fract *fract)
{
	if (fract->image_info.image)
		mlx_destroy_image(fract->mlx, fract->image_info.image);
	if (fract->window)
		mlx_destroy_window(fract->mlx, fract->window);
	if (fract->error == MEMORY_ERROR)
	{
		errno = 12;
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	exit(0);
}

void	check_overflow(t_fract *fract, t_iarea tmp_area)
{
	if (tmp_area.r_begin + DBL_MIN * 10 < tmp_area.r_last && \
		(tmp_area.i_begin + DBL_MIN * 10 < tmp_area.i_last))
	{
		fract->i_area = tmp_area;
		set_step(fract);
	}
}

void	update_display_area(t_fract *fract, t_point point, \
	   	float zoom_ratio, t_point offset)
{
	t_ipoint	distance;
	t_ipoint	ratio;
	t_ipoint	center;
	t_ipoint	zoom_center;
	t_iarea		tmp_area;

	zoom_center.r = fract->i_area.r_begin \
		+ fract->step.r * (point.x + offset.x);
	zoom_center.i = fract->i_area.i_begin \
		+ fract->step.i * ((point.y) + offset.y);
	ratio.r = (zoom_center.r - fract->i_area.r_begin) \
		/ (fract->i_area.r_last - fract->i_area.r_begin);
	ratio.i = (zoom_center.i - fract->i_area.i_begin) \
		/ (fract->i_area.i_last - fract->i_area.i_begin);
	center.r = fract->i_area.r_begin + fract->step.r * (point.x);
	center.i = fract->i_area.i_begin + fract->step.i * (point.y);
	distance.r = (fract->i_area.r_last - fract->i_area.r_begin) * zoom_ratio;
	distance.i = (fract->i_area.i_last - fract->i_area.i_begin) * zoom_ratio;
	tmp_area.r_begin = center.r - distance.r * ratio.r;
	tmp_area.r_last = center.r + distance.r * (1 - ratio.r);
	tmp_area.i_begin = center.i - distance.i * ratio.i;
	tmp_area.i_last = center.i + distance.i * (1 - ratio.i);
	check_overflow(fract, tmp_area);
}

t_ipoint	transform_ri(t_fract *fract, int x, int y)
{
	t_ipoint	point;

	point.r = fract->i_area.r_begin + fract->step.r * x;
	point.i = fract->i_area.i_begin + fract->step.i * y;
	return (point);
}

void	set_step(t_fract *fract)
{
	if (fract->w_width != 0)
		fract->step.r = (fract->i_area.r_last - fract->i_area.r_begin) \
			/ fract->w_width;
	if (fract->w_height != 0)
		fract->step.i = (fract->i_area.i_last - fract->i_area.i_begin) \
			/ fract->w_height;
}
