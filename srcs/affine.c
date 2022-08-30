/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:07:40 by hsano             #+#    #+#             */
/*   Updated: 2022/08/29 21:43:33 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "affine.h"
#include "image.h"
#include "math.h"

static t_point	calc(t_fract *fract, t_point src_point, t_point offset, t_matrix matrix)
{
	t_ipoint	point;
	t_point		rpoint;
	long		tmp;
	t_ipoint c;

	rpoint.x = 0;
	rpoint.y = 0;
	c.r = fract->i_area.r_begin + fract->step.r * (src_point.x + offset.x);
	c.i = fract->i_area.i_begin + fract->step.i * (fract->w_height - (src_point.y + offset.y) - 1);
	point.r = matrix.a * c.r + matrix.b * c.i + matrix.e;
	point.i = matrix.c * c.r + matrix.d * c.i + matrix.f;
	tmp = (int)nearbyintl(((point.r - fract->i_area.r_begin) / fract->step.r)) - offset.x;
	if (fract->w_width > tmp && tmp >= 0)
		rpoint.x = tmp;
	tmp = (int)nearbyintl(((point.i - fract->i_area.i_begin) / fract->step.i)) - offset.y;
	if (fract->w_height > tmp && tmp >= 0)
		rpoint.y = tmp;
	//printf("step %Lf, %Lf, x=%d, y=%d, r=%Lf, i=%Lf, rx=%d, ry=%d\n", fract->step.r, fract->step.i, src_point.x, src_point.y, c.r, c.i, rpoint.x, rpoint.y);
	return (rpoint);
}

t_point	save_edge(t_point affine_point, t_point edge_point)
{
	if (affine_point.y > 0 && affine_point.x > 0)
	{
		//if (edge_point.y < affine_point.y)
		if (edge_point.x > affine_point.x)
		{
			edge_point.x = affine_point.x;
			edge_point.y = affine_point.y;
		}
		printf(" edge x=%d, y=%d, affine x=%d, y=%d\n", edge_point.x, edge_point.y, affine_point.x, affine_point.y);
	}
	return (edge_point);
}


t_point	affine(t_fract *fract, void *dest_addr, t_point offset,  t_matrix matrix)
{
	int	*dst_i;
	t_point	point;
	t_point	affine_point;
	t_point	edge_point;

	edge_point.x = IMAGE_WIDTH;
	edge_point.y = 0;
	point.y = 0;
	while (point.y < IMAGE_HEIGHT)
	{
		point.x = 0;
		while (point.x < IMAGE_WIDTH)
		{
			if (!is_black(fract, fract->image_info.addr, point.x, point.y))
			{
				affine_point = calc(fract, point, offset, matrix);
				dst_i = dest_addr + fract->image_info.sl * (affine_point.y);
				dst_i[affine_point.x] = fract->defalut_color;
				edge_point =  save_edge(affine_point, edge_point);
			}
			point.x++;
		}
		point.y++;
	}
	return (edge_point);
}
