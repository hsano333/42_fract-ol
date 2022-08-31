/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:07:40 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 01:52:48 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "affine.h"
#include "image.h"
#include "math.h"

static t_point	calc(t_fract *fract \
		, t_point src_point, t_point offset, t_matrix matrix)
{
	t_ipoint	point;
	t_point		rpoint;
	long		tmp;

	rpoint.x = 0;
	rpoint.y = 0;
	point.r = matrix.a * (src_point.x + offset.x) \
	+ matrix.b * (fract->w_height - (src_point.y + offset.y) - 1) + matrix.e;
	point.i = matrix.c * (src_point.x + offset.x) \
	+ matrix.d * (fract->w_height - (src_point.y + offset.y) - 1) + matrix.f;
	tmp = (int)nearbyintl(point.r) - offset.x;
	if (fract->w_width > tmp && tmp >= 0)
		rpoint.x = tmp;
	tmp = (int)nearbyintl(point.i) - offset.y;
	if (fract->w_height > tmp && tmp >= 0)
		rpoint.y = tmp;
	return (rpoint);
}

t_area	save_edge(t_point affine_point, t_area edge_area)
{
	if (affine_point.y > 0 && affine_point.x > 0)
	{
		if (edge_area.x_begin > affine_point.x)
			edge_area.x_begin = affine_point.x;
		if (edge_area.x_last < affine_point.x)
			edge_area.x_last = affine_point.x;
		if (edge_area.y_begin > affine_point.y)
			edge_area.y_begin = affine_point.y;
		if (edge_area.y_last < affine_point.y)
			edge_area.y_last = affine_point.y;
	}
	return (edge_area);
}

t_area	affine(t_fract *fract, void *addr, t_point offset, t_matrix matrix)
{
	int		*dst_i;
	t_point	point;
	t_point	affine_point;
	t_area	edge_area;

	edge_area.x_begin = IMAGE_WIDTH;
	edge_area.x_last = 0;
	edge_area.y_begin = IMAGE_HEIGHT;
	edge_area.y_last = 0;
	point.y = -1;
	while (++point.y < IMAGE_HEIGHT)
	{
		point.x = -1;
		while (++point.x < IMAGE_WIDTH)
		{
			if (!is_black(fract, fract->image_info.addr, point.x, point.y))
			{
				affine_point = calc(fract, point, offset, matrix);
				dst_i = addr + fract->image_info.sl * (affine_point.y);
				dst_i[affine_point.x] = fract->defalut_color;
				edge_area = save_edge(affine_point, edge_area);
			}
		}
	}
	return (edge_area);
}
