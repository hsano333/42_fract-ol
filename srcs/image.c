/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 01:31:35 by hsano             #+#    #+#             */
/*   Updated: 2022/09/06 09:06:00 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"

void	mapping_color(t_fract *fract, unsigned char *ptr, int x, int color)
{
	int	opp;
	int	dec;
	int	endian;

	endian = fract->image_info.endian;
	opp = fract->image_info.bpp / 8;
	dec = opp;
	while (dec--)
	{
		if (endian && (endian == fract->local_endian))
			*(ptr + x * opp + dec) = ((unsigned char *)(&color))[4 - opp + dec];
		else if (!endian && endian == fract->local_endian)
			*(ptr + x * opp + dec) = ((unsigned char *)(&color))[dec];
		else if (endian && endian != fract->local_endian)
			*(ptr + x * opp + dec) = ((unsigned char *)(&color))[opp - 1 - dec];
		else if (!endian && endian != fract->local_endian)
			*(ptr + x * opp + dec) = ((unsigned char *)(&color))[3 - dec];
	}
}

void	loop_xy(t_fract *fract, int (*get_color)(t_fract *, t_point))
{
	int				color;
	t_point			point;
	unsigned char	*ptr;

	point.y = fract->w_height;
	while (point.y--)
	{
		if (fract->reverse_y)
			ptr = fract->image_info.addr + fract->image_info.sl * (point.y);
		else
			ptr = fract->image_info.addr \
				+ fract->image_info.sl * (fract->w_height - point.y - 1);
		point.x = fract->w_width;
		while (point.x--)
		{
			color = mlx_get_color_value(fract->mlx, get_color(fract, point));
			mapping_color(fract, ptr, point.x, color);
		}
	}
}

int	create_image(t_fract *fract)
{
	float	tmp_ratio;

	fract->diversion_count = 0;
	fract->near_diversion_count = 0;
	fract->image_info.addr = mlx_get_data_addr(fract->image_info.image \
			, &fract->image_info.bpp \
			, &fract->image_info.sl, &fract->image_info.endian);
	fract->get_image(fract);
	tmp_ratio = 0;
	if (fract->diversion_count > 0)
		tmp_ratio = (float)(100 * fract->near_diversion_count) \
			/ fract->diversion_count;
	if (tmp_ratio >= DIVERSION_COUNT_UP_THORESHOLD \
			&& (fract->iteration_max + 2 + (tmp_ratio * 10)) < INT_MAX)
		fract->iteration_max += 2 + (tmp_ratio * 10);
	else if ((tmp_ratio < DIVERSION_COUNT_DOWN_THORESHOLD) \
		&& (fract->iteration_max > INTERATION_INIT) && fract->zoom_count > 0)
	{
		fract->iteration_max -= \
			(fract->iteration_max - INTERATION_INIT) / fract->zoom_count;
	}
	return (true);
}

int	update_image(t_fract *fract)
{
	if (!fract->update_image_flag)
		return (false);
	if (fract->create_image_flag)
		create_image(fract);
	mlx_put_image_to_window(fract->mlx, fract->window, \
		   	fract->image_info.image, fract->offset.x, fract->offset.y);
	fract->update_image_flag = false;
	fract->create_image_flag = false;
	return (true);
}

void	set_init_value(t_fract *fract)
{
	int	a;

	a = 0x11223344;
	fract->init(fract);
	fract->error = NO_ERROR;
	fract->speed_thoreshold = SPEED_THRESHOLD;
	fract->w_width = IMAGE_WIDTH;
	fract->w_height = IMAGE_HEIGHT;
	fract->i_area_base = fract->i_area;
	fract->c.r = -0.12;
	fract->c.i = 0.74;
	fract->offset.x = (W_WIDTH - IMAGE_WIDTH) / 4;
	fract->offset.y = (W_HEIGHT - IMAGE_HEIGHT) / 4;
	set_step(fract);
	fract->local_endian = 0;
	if (((unsigned char *)&a)[0] == 0x11)
		fract->local_endian = 1;
}
