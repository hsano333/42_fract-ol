/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gasket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:31:41 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 09:09:57 by hsano            ###   ########.fr       */
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
#define TRIANGLE_OFFSET_Y  (100 - 400)

int	draw_triangle(t_fract *fract, t_point point)
{
	double	a1;
	double	b1;
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
			if ((a1 * tmp_point.r + b1 > tmp_point.i) && ( b1 - a1 * tmp_point.r > tmp_point.i))
			{
					return (fract->defalut_color);
			}
		}
	}
	return (0);
}

static	t_matrix get_matrix(int mode, fract_type magnification)
{
	t_matrix	matrix;

	ft_memset(&matrix, 0, sizeof(matrix));
	if (mode == 0)
	{
		matrix.a = magnification;
		matrix.d = magnification;
	}
	else if (mode == 1 || mode == 3)
	{
		matrix.a = (fract_type)1 / 3;
		matrix.b = 0;
		matrix.c = 0;
		matrix.d = (fract_type)1 / 3;
		matrix.e = (fract_type)1 / 3;
		matrix.f = 0;
		if (mode == 3)
			matrix.e = (fract_type)2 / 3;
	}
	else if (mode == 2)
	{
		matrix.a = (fract_type)1 / 6;
		matrix.b = -sqrt(3) / 6;
		matrix.c = sqrt(3) / 6;
		matrix.d = (fract_type)1 / 6;
		matrix.e = (fract_type)1 / 3;
		matrix.f = 0;
	}
	else if (mode == 3)
	{
		matrix.a = (fract_type)1 / 6;
		matrix.b = sqrt(3) / 6;
		matrix.c = -sqrt(3) / 6;
		matrix.d = (fract_type)1 / 6;
		matrix.e = (fract_type)1 / 2;
		matrix.f = sqrt(3) / 6;
	}
	return (matrix);
}

int	update_gasket(t_fract *fract, int matrix_mode)
{
	t_img	*new_image ;
	void	*new_addr;
	t_point offset;
	t_matrix	matrix;
	t_area	edge_area;

	new_image = (void *)mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!new_image)
		close_fract(fract);
	new_addr = mlx_get_data_addr(new_image, &fract->image_info.bpp, &fract->image_info.sl, &fract->image_info.endian);
	offset.y = TRIANGLE_LENGTH / sqrt(3) * 0.5 - IMAGE_HEIGHT * 0.5;
	offset.x = -IMAGE_WIDTH * 0.5;
	matrix = get_matrix(matrix_mode , 0.5);
	edge_area =  affine(fract, new_addr, offset, matrix);
	clear_image(fract, fract->image_info.image);
	offset.x = -edge_area.x_begin + TRIANGLE_OFFSET_X / 2;
	offset.y = 0;
	overlapping_image(fract, new_image, offset);
	offset.x += edge_area.x_last - edge_area.x_begin + 1 ;
	offset.y += 0;
	overlapping_image(fract, new_image, offset);
	offset.x -= (edge_area.x_last - edge_area.x_begin) / 2;
	offset.y += ((edge_area.y_last - edge_area.y_begin) + 1) ;
	overlapping_image(fract, new_image, offset);
	mlx_destroy_image(fract->mlx, new_image);

	fract->image_info.edge_area = edge_area;
	return (true);
}

void	zoom_gasket(t_fract *fract)
{
	t_point offset;
	t_area	edge_area;
	t_img	*new_image ;
	void	*new_addr;
	t_matrix	matrix;

	new_image = (void *)mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!new_image)
		close_fract(fract);
	new_addr = mlx_get_data_addr(new_image, &fract->image_info.bpp, &fract->image_info.sl, &fract->image_info.endian);
	edge_area =  affine(fract, new_addr, offset, matrix);
	offset.x = -edge_area.x_begin + TRIANGLE_OFFSET_X;
	offset.y = 0;

	matrix = get_matrix(0, fract->zoom_ratio);
	edge_area =  affine(fract, new_addr, offset, matrix);

	clear_image(fract, fract->image_info.image);
	offset.x = -edge_area.x_begin + TRIANGLE_OFFSET_X;
	offset.y = 0;
	overlapping_image(fract, new_image, offset);

}

int	get_gasket_image(t_fract *fract)
{
	t_point point;

	point.x = 0;
	point.y = 0;
	update_display_area(fract, point, 1, point);
	loop_xy(fract, draw_triangle);
	update_gasket(fract, 0);
	update_gasket(fract, 0);
	update_gasket(fract, 0);
	update_gasket(fract, 0);
	update_gasket(fract, 0);
	update_gasket(fract, 0);
	update_gasket(fract, 0);
	update_gasket(fract, 0);
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
