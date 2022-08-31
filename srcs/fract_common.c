/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 05:38:17 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 09:05:05 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"

int	unlock(t_fract *fract)
{
	fract->lock = false;
	return (true);
}

int	close_fract(t_fract *fract)
{
	//ft_printf("close_fracti test No1\n");
	//if (image != NULL)
		//mlx_destroy_image(fract->mlx, image);
	if (fract->image_info.image)
		mlx_destroy_image(fract->mlx, fract->image_info.image);
	//if (fract->image_backup)
		//mlx_destroy_image(fract->mlx, fract->image_backup);
	mlx_destroy_window(fract->mlx, fract->window);
	exit(0);

	return (0);
}

void	set_step(t_fract *fract)
{
	if (fract->w_width != 0)
		fract->step.r = (fract->i_area.r_last - fract->i_area.r_begin) / fract->w_width;
	if (fract->w_height != 0)
		fract->step.i = (fract->i_area.i_last - fract->i_area.i_begin) / fract->w_height;
	//fract->base_size = (fract->i_area.i_last - fract->i_area.i_begin) * 0.75;

}

void	update_display_area(t_fract *fract, t_point point, float zoom_ratio, t_point offset)
{
	t_ipoint	distance;
	t_ipoint	ratio;
	t_ipoint	center;
	t_ipoint	zoom_center;
	t_iarea	tmp_area;

	zoom_center.r = fract->i_area.r_begin + fract->step.r * (point.x + offset.x);
	zoom_center.i = fract->i_area.i_begin + fract->step.i * (point.y + offset.y);
	ratio.r = (zoom_center.r - fract->i_area.r_begin) / (fract->i_area.r_last - fract->i_area.r_begin);
	ratio.i = (zoom_center.i - fract->i_area.i_begin) / (fract->i_area.i_last - fract->i_area.i_begin);
	center.r = fract->i_area.r_begin + fract->step.r * (point.x);
	center.i = fract->i_area.i_begin + fract->step.i * (point.y);
	distance.r = (fract->i_area.r_last - fract->i_area.r_begin) * zoom_ratio;
	distance.i = (fract->i_area.i_last - fract->i_area.i_begin) * zoom_ratio;
	tmp_area.r_begin = center.r - distance.r * ratio.r;
	tmp_area.r_last  = center.r + distance.r * (1 - ratio.r);
	tmp_area.i_begin = center.i - distance.i * ratio.i;
	tmp_area.i_last = center.i + distance.i * (1 - ratio.i);
	if (tmp_area.r_begin + DBL_MIN * 10  < tmp_area.r_last && 
		(tmp_area.i_begin + DBL_MIN * 10 < tmp_area.i_last))
	{
		fract->i_area = tmp_area;
		set_step(fract);
	}
}

/*
t_ipoint	convert_dpoint_to_ipoint(t_fract *fract, t_point point)
{
	t_ipoint ipoint;
	ipoint.z = 
}

*/
