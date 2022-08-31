/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:14:25 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 01:15:54 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int	get_color_point(t_fract *fract, int x, int y)
{
	int				opp;
	int				dec;
	int				endian;
	int				color;
	unsigned char	*ptr;

	if ((fract->w_width > x && x >= 0) || (fract->w_height > y && y >= 0))
		return (0);
	ptr = fract->image_info.addr \
		+ fract->image_info.sl * (fract->w_height - y - 1);
	endian = fract->image_info.endian;
	opp = fract->image_info.bpp / 8;
	dec = opp;
	while (dec--)
	{
		if (endian && endian == fract->local_endian)
			*(ptr + x * opp + dec) = ((unsigned char *)(&color))[4 - opp + dec];
		else if (!endian && endian == fract->local_endian)
			*(ptr + x * opp + dec) = ((unsigned char *)(&color))[dec];
		else if (endian && endian != fract->local_endian)
			*(ptr + x * opp + dec) = ((unsigned char *)(&color))[opp - 1 - dec];
		else if (!endian && endian != fract->local_endian)
			*(ptr + x * opp + dec) = ((unsigned char *)(&color))[3 - dec];
	}
	return (ptr[x]);
}

int	is_black(t_fract *fract, void *addr, int x, int y)
{
	int				opp;
	int				dec;
	unsigned char	*ptr;

	if (!(fract->w_width > x && x >= 0))
		return (true);
	if (!(fract->w_height > y && y >= 0))
		return (true);
	ptr = addr + fract->image_info.sl * (fract->w_height - y - 1);
	opp = fract->image_info.bpp / 8;
	dec = opp;
	while (--dec)
	{
		if (*(ptr + x * opp + dec) > 0)
			return (false);
	}
	return (true);
}

void	clear_image(t_fract *fract, t_img *image)
{
	int				sl;
	int				bpp;
	void			*addr;
	t_point			point;
	unsigned int	*src_ptr;

	addr = mlx_get_data_addr(image, &bpp, &sl, &fract->image_info.endian);
	point.y = fract->w_height;
	while (point.y--)
	{
		src_ptr = addr + sl * point.y;
		point.x = fract->w_width;
		while (point.x--)
		{
			src_ptr[point.x] = 0;
		}
	}
}

void	overlapping_image(t_fract *fract, t_img *image, t_point offset)
{
	int				sl;
	int				bpp;
	void			*addr;
	t_point			point;
	unsigned int	*dst_ptr;

	addr = mlx_get_data_addr(image, &bpp, &sl, &fract->image_info.endian);
	point.y = fract->w_height;
	while (point.y--)
	{
		if (!(0 <= fract->w_height - (point.y + offset.y) - 1 \
				&& fract->w_height - (point.y + offset.y) - 1 < IMAGE_HEIGHT))
			continue ;
		dst_ptr = fract->image_info.addr \
		+ fract->image_info.sl * (fract->w_height - (point.y + offset.y) - 1);
		point.x = fract->w_width;
		while (point.x--)
		{
			if (!is_black(fract, addr, point.x, point.y) \
				&& 0 <= point.x + offset.x && point.x + offset.x < IMAGE_WIDTH)
				dst_ptr[point.x + offset.x] = fract->defalut_color;
		}
	}
}

void	*copy_image(t_fract *fract)
{
	void			*addr;
	void			*new_image;
	t_point			point;
	unsigned int	*source_ptr;
	unsigned int	*dst_ptr;

	new_image = (void *)mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!new_image)
		close_fract(fract);
	addr = mlx_get_data_addr(new_image, &fract->image_info.bpp, \
		   	&fract->image_info.sl, &fract->image_info.endian);
	point.y = fract->w_height;
	while (point.y--)
	{
		dst_ptr = addr + fract->image_info.sl * (fract->w_height - point.y - 1);
		source_ptr = fract->image_info.addr + \
			fract->image_info.sl * (fract->w_height - point.y - 1);
		point.x = fract->w_width;
		while (point.x--)
			dst_ptr[point.x] = source_ptr[point.x];
	}
	return (new_image);
}
