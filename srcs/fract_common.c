/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 05:38:17 by hsano             #+#    #+#             */
/*   Updated: 2022/08/23 19:37:08 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"

void	set_step(t_fract *fract)
{
	if (fract->w_width != 0)
		fract->step.r = (fract->i_area.r_last - fract->i_area.r_begin) / fract->w_width;
	if (fract->w_height != 0)
		fract->step.i = (fract->i_area.i_last - fract->i_area.i_begin) / fract->w_height;

}

void	update_display_area(t_fract *fract, t_point point, float zoom_ratio)
{
	float	r_distance;
	float	i_distance;
	t_ipoint	ratio;
	t_ipoint	center;
	t_ipoint	zoom_center;
	//t_ipoint	tmp;
	

	zoom_center.r = fract->i_area.r_begin + fract->step.r * point.x;
	zoom_center.i = fract->i_area.i_begin + fract->step.i * point.y;

	ratio.r = (zoom_center.r - fract->i_area.r_begin) / (fract->i_area.r_last - fract->i_area.r_begin);
	ratio.i = (zoom_center.i - fract->i_area.i_begin) / (fract->i_area.i_last - fract->i_area.i_begin);

	center.r = fract->i_area.r_begin + fract->step.r * point.x;
	center.i = fract->i_area.i_begin + fract->step.i * point.y;
	//center.r = fract->i_area.r_begin + ratio.r;
	//center.i = fract->i_area.i_begin + ratio.i;
	//center.r = (fract->i_area.r_last - fract->i_area.r_begin)/2;
	//center.i = (fract->i_area.i_last - fract->i_area.i_begin)/2;

	printf("before chage:r_begin=%f, r_last=%f,i_begin=%f, i_last=%f, step.r=%f, step.i=%f\n ",fract->i_area.r_begin,fract->i_area.r_last,fract->i_area.i_begin, fract->i_area.i_last,fract->step.r,fract->step.i);
	r_distance = (fract->i_area.r_last - fract->i_area.r_begin) * zoom_ratio;
	i_distance = (fract->i_area.i_last - fract->i_area.i_begin) * zoom_ratio;
	//r_distance = (fract->i_area.r_last - fract->i_area.r_begin) * zoom_ratio / 2;
	//i_distance = (fract->i_area.i_last - fract->i_area.i_begin) * zoom_ratio / 2;
	if (center.r - r_distance * ratio.r < center.r + r_distance * (1 - ratio.r) && center.i - i_distance * ratio.i < center.i + i_distance * (1 - ratio.i))
	{
		fract->i_area.r_begin = center.r - r_distance * ratio.r;
		fract->i_area.r_last = center.r + r_distance * (1 - ratio.r);
		fract->i_area.i_begin = center.i - i_distance * ratio.i;
		fract->i_area.i_last = center.i + i_distance * (1 - ratio.i);
		set_step(fract);
	}
	printf("after change:r_begin=%f, r_last=%f,i_begin=%f, i_last=%f, step.r=%f, step.i=%f\n ",fract->i_area.r_begin,fract->i_area.r_last,fract->i_area.i_begin, fract->i_area.i_last,fract->step.r,fract->step.i);
	printf("after r_distance:%f  ratio.r:%f, i_distance:%f  ratio.i:%f\n", r_distance, ratio.r, i_distance, ratio.i);
}

/*
t_ipoint	convert_dpoint_to_ipoint(t_fract *fract, t_point point)
{
	t_ipoint ipoint;
	ipoint.z = 
}

*/
