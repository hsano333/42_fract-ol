/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:07:40 by hsano             #+#    #+#             */
/*   Updated: 2022/08/28 19:04:33 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "affine.h"
#include "image.h"
#include "math.h"

static t_point	calc(t_point src_point, t_matrix matrix)
{
	t_ipoint	point;
	t_point		rpoint;
	long		tmp;

	rpoint.x = 0;
	rpoint.y = 0;
	//printf("affine test NO.3 calc, point x=%d, y=%d,, a=%lf, b=%lf, c=%lf, d=%lf, \n", src_point.x, src_point.y, matrix.a, matrix.b, matrix.c, matrix.d);
	point.r = matrix.a * (fract_type)src_point.x + matrix.b * (fract_type)src_point.y + matrix.e;
	point.i = matrix.c * (fract_type)src_point.x + matrix.d * (fract_type)src_point.y + matrix.f;
	tmp = nearbyintl(point.r);
	if (W_WIDTH > tmp && tmp >= 0)
		rpoint.x = nearbyintl(point.r);
	tmp = nearbyintl(point.i);
	if (W_HEIGHT > tmp && tmp >= 0)
		rpoint.y = nearbyintl(point.i);
	//printf("rpoint: x=%d, y=%d/n", rpoint.x, rpoint.y);
	return (rpoint);
}

//void	affine(t_fract *fract, void *dest_addr, t_point (*convert_point)(t_fract *, t_point))
void	affine(t_fract *fract, void *dest_addr, t_matrix matrix)
{
	//int	*old_i;
	int	*dst_i;
	t_point	point;
	t_point	affine_point;


	printf("dest_addr=%p\n", dest_addr);
	//printf("affine test NO.1\n");
	//dst_i = fract->image_info.addr;
	point.y = 0;
	while (point.y < IMAGE_HEIGHT)
	{
		//old_i = fract->image_info.addr + fract->image_info.sl * (fract->w_height - point.y - 1);
		point.x = 0;
		while (point.x < IMAGE_WIDTH)
		{
			if (!is_black(fract, point.x, point.y))
			{
				affine_point = calc(point, matrix);
				printf("affine test NO.2 ori:x:%d, y:%d, convert  x*%d, y=%d\n",point.x, point.y ,affine_point.x, affine_point.y);
				//affine_point = convert_point(fract, point);
				
				dst_i = dest_addr + fract->image_info.sl * (fract->w_height - affine_point.y - 1);
				//dst_i[affine_point.x] = old_i[point.x];
				dst_i[affine_point.x] = ((255 << 16) + (255 << 8) + 255);
			}
			point.x++;
		}
		point.y++;
	}
}
