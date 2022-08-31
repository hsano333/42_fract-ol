/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:31:41 by hsano             #+#    #+#             */
/*   Updated: 2022/08/30 20:37:45 by hsano            ###   ########.fr       */
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

//int	draw_triangle(t_fract *fract, t_point point)
//{
//	double	a1;
//	double	a2;
//	double	b1;
//	double	b2;
//	t_point	tmp_point;
//
//	if (TRIANGLE_OFFSET_X <= point.x && point.x < TRIANGLE_OFFSET_X + TRIANGLE_LENGTH)
//	{
//		if (TRIANGLE_OFFSET_Y <= point.y && point.y <= TRIANGLE_OFFSET_Y + 2)
//			return (fract->defalut_color);
//		tmp_point.x = point.x - IMAGE_WIDTH / 2;
//		tmp_point.y = point.y - IMAGE_HEIGHT / 2;
//		a1 = sqrt(3);
//		a2 = -a1;
//		b1 = ((TRIANGLE_OFFSET_Y - IMAGE_HEIGHT / 2)) - (TRIANGLE_OFFSET_X - IMAGE_WIDTH / 2) * a1;
//		b2 = ((TRIANGLE_OFFSET_Y - IMAGE_HEIGHT / 2)) - (TRIANGLE_OFFSET_X - IMAGE_WIDTH / 2 + TRIANGLE_LENGTH) * a2;
//		if (tmp_point.x < 0 &&  a1 * tmp_point.x + b1 <= tmp_point.y && tmp_point.y <  a1 * tmp_point.x + b1 + 3)
//			return (fract->defalut_color);
//		if (tmp_point.x >= 0 && a2 * tmp_point.x + b2 <= tmp_point.y && tmp_point.y <  a2 * tmp_point.x + b2 + 3)
//			return (fract->defalut_color);
//	}
//	return (0);
//}

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

//static int	init_triangle(t_fract *fract)
//{
//	//int		begin_x;
//	//static int	x_count = 0;
//	t_matrix	matrix;
//	void	*new_addr;
//	t_img	*tmp_image;
//
//	/*
//	if (point.x == 0 && point.y == 0)
//		x_count = 0;
//	if (!(LAST_Y >= point.y && point.y >= BEGIN_Y))
//		return (0);
//	if (point.x == 0)
//		x_count++;
//	begin_x = fract->w_width / 2 - x_count - 15;
//	//if (begin_x + 2 * x_count > x && x > begin_x)
//	if (point.y == BEGIN_Y && (begin_x + 2 * x_count > point.x) && point.x > begin_x)
//		return (fract->defalut_color);
//	if (begin_x + 2 * x_count == point.x || point.x == begin_x)
//		return (fract->defalut_color);
//	*/
//
//	//loop_xy(fract, draw_line);
//	matrix.a = (double)1/2;
//	matrix.b = -sqrt(3) / 2;
//	matrix.c = sqrt(3) / 2;
//	matrix.d = (double)1/2;
//	//matrix.e = 0;
//	matrix.e = 0;
//	matrix.f = 0;
//	/*
//	matrix.a = 0.5;
//	matrix.b = -sqrt(3) / 2;
//	matrix.c = sqrt(3) / 2;
//	matrix.d = 0.5;
//	matrix.e = TRIANGLE_OFFSET_X;
//	matrix.f = 0;
//	*/
//	tmp_image = (void *)mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
//	if (!tmp_image)
//		close_fract(fract);
//	new_addr = mlx_get_data_addr(tmp_image, &fract->image_info.bpp, &fract->image_info.sl, &fract->image_info.endian);
//	t_point offset;
//
//	//offset.x = -TRIANGLE_LENGTH / 2;
//	//offset.y = -TRIANGLE_LENGTH / 2;
//	offset.x = TRIANGLE_LENGTH / 2;
//	offset.y = 190;
//
//	affine(fract, new_addr, offset, matrix);
//	return (0);
//	overlapping_image(fract, tmp_image);
//
//
//	clear_image(fract, tmp_image);
//	//tmp_image = (void *)mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
//	matrix.a = 0.5;
//	matrix.b = +sqrt(3) / 2;
//	matrix.c = -sqrt(3) / 2;
//	matrix.d = 0.5;
//	matrix.e = TRIANGLE_LENGTH / 4;
//	matrix.f = sqrt(3) * TRIANGLE_LENGTH / 12;
//	//if (!tmp_image)
//		//close_fract(fract);
//	//new_addr = mlx_get_data_addr(tmp_image, &fract->image_info.bpp, &fract->image_info.sl, &fract->image_info.endian);
//	affine(fract, new_addr, offset, matrix);
//	//overlapping_image(fract, tmp_image);
//	//mlx_destroy_image(fract->mlx, tmp_image);
//
//	return (0);
//}

/*
static int	calc_color(t_fract *fract, int x, int y)
{

	printf("x:%d, y:%d, fract=%p\n", x, y, fract);
	return (0);
}
*/


void	calc_koch(t_fract *fract, void *new_addr)
{

	//int	*src_i;
	//int	*old_i;
	//int	tmp_addr;
	//t_point	point;
	//t_point		src_point;
	t_matrix	matrix;
	/*
	point.y = 0;
	//src_i = fract->image_info.addr;
	while (point.y < IMAGE_HEIGHT)
	{
		//src_i = fract->image_info.addr + fract->image_info.sl * (fract->w_height - point.y - 1);
		old_i = old_addr + fract->image_info.sl * (fract->w_height - point.y - 1);
		point.x = 0;
		while (point.x < IMAGE_WIDTH)
		{
			src_point.x = point.x / 3 + (fract->w_width / 2 - 15) *2 / 3;
			src_point.y = point.y / 3 + 400 * 2 / 3;
			src_i = fract->image_info.addr + fract->image_info.sl * (fract->w_height - src_point.y - 1);
			src_i[src_point.x] = old_i[point.x];
			//src_i[point.x / 3] = old_i[point.x];
			//src_i[point.x / 3] = old_i[point.x];
			point.x++;
		}
		point.y++;
	}
	*/
	matrix.a = 0.333333;
	matrix.b = 0.0;
	matrix.c = 0.0;
	matrix.d = 0.3333333;
	matrix.e = 0.0;
	matrix.f = 0.0;
	//printf("new_addr=%p\n", new_addr);
	t_point offset;

	offset.x = TRIANGLE_OFFSET_X;
	offset.y = 80;
	affine(fract, new_addr, offset, matrix);
	matrix.a = 0.333333333333333333333333;
	matrix.b = -0.333333333333333333333333;
	matrix.c = 0.333333333333333333333333;
	matrix.d = 0.333333333333333333333333;
	matrix.e = 0.333333333333333333333333;
	matrix.f = 0.0;
	//printf("new_addr=%p\n", new_addr);
	affine(fract, new_addr, offset, matrix);

	//old_i[0][0] = 0;
	//src_i[0][0] = 0;
	printf("end update koch \n");
	printf("end update koch \n");
	printf("end update koch \n");
	printf("end update koch \n");
	printf("end update koch \n");
}

int	update_koch(t_fract *fract, int matrix_mode)
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

void	set_init(t_fract *fract)
{
	fract->i_area.r_begin = -TRIANGLE_LENGTH;
	fract->i_area.r_last = TRIANGLE_LENGTH;
	fract->i_area.i_begin = -TRIANGLE_LENGTH;
	fract->i_area.i_last = TRIANGLE_LENGTH;
	fract->i_area_base = fract->i_area;

}

void	zoom_koch(t_fract *fract)
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
	/*
	edge_area = fract->image_info.edge_area;
	offset.x = -edge_area.x_begin + TRIANGLE_OFFSET_X;
	offset.y = 0;
	//overlapping_image(fract, new_image, offset);
	offset.x = (edge_area.x_last - edge_area.x_begin) * 2 + 1 ;
	offset.y = 0;
	overlapping_image(fract, fract->image_info.backup_image, offset);
	offset.x -= (edge_area.x_last - edge_area.x_begin);
	offset.y += ((edge_area.y_last - edge_area.y_begin) * 2 + 1) ;
	overlapping_image(fract, fract->image_info.backup_image, offset);
	*/

	//matrix = get_matrix(0);
	////printf("zzom :%p\n",fract);
	//new_addr = mlx_get_data_addr(fract->image_info.backup_image, &fract->image_info.bpp, &fract->image_info.sl, &fract->image_info.endian);
	//edge_area =  affine(fract, new_addr, offset, matrix);
	//update_koch(fract, 1);

}

int	get_koch_image(t_fract *fract)
{
	t_point point;

	point.x = 0;
	point.y = 0;
	if (fract->iteration_max == INTERATION_INIT)
	{
		set_init(fract);
		/*
		fract->i_area.r_begin = -TRIANGLE_LENGTH;
		fract->i_area.r_last = TRIANGLE_LENGTH;
		fract->i_area.i_begin = -TRIANGLE_LENGTH;
		fract->i_area.i_last = TRIANGLE_LENGTH;
		*/
		update_display_area(fract, point, 1, point);
		loop_xy(fract, draw_triangle);
		update_koch(fract, 0);
		update_koch(fract, 0);
		update_koch(fract, 0);
		update_koch(fract, 0);
		update_koch(fract, 0);
		update_koch(fract, 0);
		update_koch(fract, 0);
		update_koch(fract, 0);
		fract->image_info.backup_image = copy_image(fract);
		return (true);
	}

	//update_display_area(fract, point, 1, point);
	/*
	loop_xy(fract, draw_triangle);
	update_koch(fract);
	update_koch(fract);
	update_koch(fract);
	update_koch(fract);
	update_koch(fract);
	update_koch(fract);
	*/
		//loop_xy(fract, draw_triangle);
		//update_koch(fract, 0);
		//update_koch(fract, 0);
		//update_koch(fract, 0);
		//update_koch(fract, 0);
		//update_koch(fract, 0);
		//update_koch(fract, 0);
		//update_koch(fract, 0);
		//update_koch(fract, 0);
		//update_koch(fract, 0);
		//fract->image_info.backup_image = copy_image(fract);
		/*
	zoom_koch(fract);
	zoom_koch(fract);
	zoom_koch(fract);
	zoom_koch(fract);
	zoom_koch(fract);
	zoom_koch(fract);
	zoom_koch(fract);
	zoom_koch(fract);
	zoom_koch(fract);
	*/
	zoom_koch(fract);
	return (0);
	//return (update_koch(fract));
}
