/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:14:25 by hsano             #+#    #+#             */
/*   Updated: 2022/08/30 18:26:48 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"



int	get_color_point(t_fract *fract, int x, int y)
{
	unsigned char	*ptr;
	int		opp;
	int 		dec;
	int	endian;
	int	color;


	if (fract->w_width > x && x >= 0)
		return (0);
	if (fract->w_height > y && y >= 0)
		return (0);
	ptr = fract->image_info.addr + fract->image_info.sl * (fract->w_height - y - 1);

	       
	endian = fract->image_info.endian;
	opp = fract->image_info.bpp/8;
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

int	is_black(t_fract *fract, void *addr,  int x, int y)
{
	unsigned char	*ptr;
	int		opp;
	int 		dec;
	//int	endian;
	//int	color;


	//printf("black test No.1\n");
	if (!(fract->w_width > x && x >= 0))
		return (true);

	//printf("black test No.2\n");
	if (!(fract->w_height > y && y >= 0))
		return (true);
	//ptr = fract->image_info.addr + fract->image_info.sl * (fract->w_height - y - 1);
	ptr = addr + fract->image_info.sl * (fract->w_height - y - 1);
	opp = fract->image_info.bpp/8;
	dec = opp;
	/*
	while (dec--)
	{
	    if (endian && endian == fract->local_endian)
		    color = 
		  *(ptr + x * opp + dec) = ((unsigned char *)(&color))[4 - opp + dec];
	    else if (!endian && endian == fract->local_endian)
		  *(ptr + x * opp + dec) = ((unsigned char *)(&color))[dec];
	    else if (endian && endian != fract->local_endian)
		  *(ptr + x * opp + dec) = ((unsigned char *)(&color))[opp - 1 - dec];
	    else if (!endian && endian != fract->local_endian)
		  *(ptr + x * opp + dec) = ((unsigned char *)(&color))[3 - dec];
	}
	*/

	//printf("black test No.3 x=%d, y=%d\n", x, y);
	//printf("dec=%d\n",dec);
	
	while (--dec)  
	{
		if (*(ptr + x * opp + dec) > 0)
			return (false);
	}
	//if (*(ptr + x * opp + dec) == 0)
		//return (true);
	//printf("black test No.4\n");
	return (true);
}

void	clear_image(t_fract *fract, t_img *image)
{
	unsigned int*	src_ptr;
	//unsigned int*	dst_ptr;
	t_point	point;
	void	*addr;
	int	sl;
	int	bpp;

	addr = mlx_get_data_addr(image, &bpp, &sl, &fract->image_info.endian);
	printf(" test No.3 over new_adr=%p\n",addr);
	point.y = fract->w_height;
	while (point.y--)
	{
		src_ptr = addr + sl * point.y;
		//dst_ptr = fract->image_info.addr + fract->image_info.sl * point.y;
		//printf("sl=%d,fsl=%d\n", sl,  fract->image_info.sl);
		point.x = fract->w_width;
		//while (point.x-- && !is_black(fract, addr, point.x, point.y))
		while (point.x--)
		{
			src_ptr[point.x] = 0;
		}
	}
}

void	overlapping_image(t_fract *fract, t_img *image, t_point offset)
{
	unsigned int*	dst_ptr;
	t_point	point;
	void	*addr;
	int	sl;
	int	bpp;

	addr = mlx_get_data_addr(image, &bpp, &sl, &fract->image_info.endian);
	point.y = fract->w_height;
	while (point.y--)
	{
		//src_ptr = addr + sl * point.y;
		if (!(0 <= fract->w_height - (point.y + offset.y) - 1  && fract->w_height - (point.y + offset.y) - 1 < IMAGE_HEIGHT))
			continue;
		dst_ptr = fract->image_info.addr + fract->image_info.sl * (fract->w_height - (point.y + offset.y) - 1);
		//dst_ptr = fract->image_info.addr + fract->image_info.sl * (point.y + offset.y);
		//printf("sl=%d,fsl=%d\n", sl,  fract->image_info.sl);
		point.x = fract->w_width;
		//while (point.x-- && !is_black(fract, addr, point.x, point.y))
		while (point.x--)
		{
			//if (src_ptr[point.x] > 0 || dst_ptr[point.x] > 0)
			if (!is_black(fract, addr, point.x, point.y) && 0 <= point.x + offset.x && point.x + offset.x < IMAGE_WIDTH)
				dst_ptr[point.x + offset.x] = fract->defalut_color;

		}
	}
}

void	*copy_image(t_fract *fract)
{
	unsigned int*	source_ptr;
	unsigned int*	dst_ptr;
	t_point	point;
	void	*addr;
	void	*new_image;

	new_image = (void *)mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!new_image)
		close_fract(fract);
	addr = mlx_get_data_addr(new_image, &fract->image_info.bpp, &fract->image_info.sl, &fract->image_info.endian);
	point.y = fract->w_height;
	while (point.y--)
	{
		dst_ptr = addr + fract->image_info.sl * (fract->w_height - point.y - 1);
		source_ptr = fract->image_info.addr + fract->image_info.sl * (fract->w_height - point.y - 1);
		point.x = fract->w_width;
		while (point.x--)
			dst_ptr[point.x] = source_ptr[point.x];
	}
	return (new_image);
}
