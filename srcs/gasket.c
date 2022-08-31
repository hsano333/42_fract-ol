/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gasket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:31:41 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 01:37:49 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "color.h"
#include "image.h"
#include "affine.h"
#include "math.h"
#include "libft_mem.h"

#define TRIANGLE_LENGTH 420
#define TRIANGLE_OFFSET_X  150
#define TRIANGLE_OFFSET_Y  (-300)

int	draw_triangle(t_fract *fract, t_point point)
{
	double		a1;
	double		b1;
	t_ipoint	tmp_point;
	t_ipoint	base_point;

	base_point.r = TRIANGLE_OFFSET_X;
	base_point.i = TRIANGLE_OFFSET_Y;
	tmp_point = transform_ri(fract, point.x, point.y);
	{
		if ((base_point.i < tmp_point.i))
		{
			a1 = sqrt(3);
			b1 = TRIANGLE_LENGTH / sqrt(3);
			if ((a1 * tmp_point.r + b1 > tmp_point.i) \
					&& (b1 - a1 * tmp_point.r > tmp_point.i))
			{
				return (fract->defalut_color);
			}
		}
	}
	return (0);
}

static t_img	*create_tmp_image(t_fract fract, t_area *edge_area)
{
	void		*new_addr;
	t_img		*new_image;
	t_point		offset;
	t_matrix	matrix;

	ft_memset(&matrix, 0, sizeof(matrix));
	matrix.a = 0.5;
	matrix.d = 0.5;
	new_image = (void *)mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!new_image)
		close_fract(fract);
	new_addr = mlx_get_data_addr(new_image, &fract->image_info.bpp \
			, &fract->image_info.sl, &fract->image_info.endian);
	offset.y = TRIANGLE_LENGTH / sqrt(3) * 0.5 - IMAGE_HEIGHT * 0.5;
	offset.x = -IMAGE_WIDTH * 0.5;
	*edge_area = affine(fract, new_addr, offset, matrix);
	return (new_image);
}

int	update_gasket(t_fract *fract)
{
	t_img		*new_image;
	t_area		edge_area;
	t_point		offset;
	t_matrix	matrix;

	new_image = create_tmp_image(fract, &edge_area);
	clear_image(fract, fract->image_info.image);
	offset.x = -edge_area.x_begin + TRIANGLE_OFFSET_X / 2;
	offset.y = 0;
	overlapping_image(fract, new_image, offset);
	offset.x += edge_area.x_last - edge_area.x_begin + 1 ;
	offset.y += 0;
	overlapping_image(fract, new_image, offset);
	offset.x -= (edge_area.x_last - edge_area.x_begin) / 2;
	offset.y += ((edge_area.y_last - edge_area.y_begin) + 1);
	overlapping_image(fract, new_image, offset);
	mlx_destroy_image(fract->mlx, new_image);
	fract->image_info.edge_area = edge_area;
	return (true);
}

int	get_gasket_image(t_fract *fract)
{
	t_point	point;

	point.x = 0;
	point.y = 0;
	update_display_area(fract, point, 1, point);
	loop_xy(fract, draw_triangle);
	update_gasket(fract);
	update_gasket(fract);
	update_gasket(fract);
	update_gasket(fract);
	update_gasket(fract);
	update_gasket(fract);
	update_gasket(fract);
	update_gasket(fract);
	return (true);
}

void	init_gasket(t_fract *fract)
{
	fract->fract_set = GASKET;
	fract->get_image = (int (*)())get_gasket_image;
	fract->i_area.r_begin = -TRIANGLE_LENGTH;
	fract->i_area.r_last = TRIANGLE_LENGTH;
	fract->i_area.i_begin = -TRIANGLE_LENGTH;
	fract->i_area.i_last = TRIANGLE_LENGTH;
	fract->i_area_base = fract->i_area;
	fract->calc_color = (int (*)())calc_color1;
	fract->defalut_color = ((255 << 16) + (255 << 8) + 255);
}
