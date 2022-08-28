/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:31:41 by hsano             #+#    #+#             */
/*   Updated: 2022/08/28 18:58:28 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "color.h"
#include "image.h"
#include "affine.h"

#define BEGIN_Y 200
#define LAST_Y 400

static int	init_triangle(t_fract *fract, t_point point)
{
	int		begin_x;
	static int	x_count = 0;
	int		color;

	color = ((255 << 16) + (255 << 8) + 255);
	if (point.x == 0 && point.y == 0)
		x_count = 0;
	if (!(LAST_Y >= point.y && point.y >= BEGIN_Y))
		return (0);
	if (point.x == 0)
		x_count++;
	begin_x = fract->w_width / 2 - x_count - 15;
	//if (begin_x + 2 * x_count > x && x > begin_x)
	if (point.y == BEGIN_Y && (begin_x + 2 * x_count > point.x) && point.x > begin_x)
		return (color);
	if (begin_x + 2 * x_count == point.x || point.x == begin_x)
		return (color);
	return (0);
}

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
	printf("new_addr=%p\n", new_addr);
	affine(fract, new_addr, matrix);

	//old_i[0][0] = 0;
	//src_i[0][0] = 0;
	printf("end update koch \n");
	printf("end update koch \n");
	printf("end update koch \n");
	printf("end update koch \n");
	printf("end update koch \n");
}

int	update_koch(t_fract *fract)
{
	t_img	*new_image;
	void	*new_addr;

	new_image = (void *)mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	printf("new_image test No.1\n");
	if (!new_image)
	{
		printf("new_image test No.2\n");
		close_fract(fract);
		return (0);
	}
	//new_addr = copy_image(fract, new_image);
	new_addr = mlx_get_data_addr(new_image, &fract->image_info.bpp, &fract->image_info.sl, &fract->image_info.endian);
	//fract->image_info.addr = mlx_get_data_addr(fract->image_info.image, &fract->image_info.bpp, 
			//&fract->image_info.sl, &fract->image_info.endian);
	calc_koch(fract, new_addr);
	mlx_destroy_image(fract->mlx, fract->image_info.image);
	fract->image_info.image = new_image;
	fract->image_info.addr = new_addr;

	//printf("%p,%p\n", fract, new_image);
	//mlx_destroy_image(fract->mlx, new_image);
	return (true);
}

int	get_koch_image(t_fract *fract)
{
	fract->zoom_count++;
	fract->zoom_count--;
	if (fract->iteration_max == INTERATION_INIT)
	{
		loop_xy(fract, init_triangle);
		return (true);
	}
	return (update_koch(fract));
}
