/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 01:31:35 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 09:23:04 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"

void	mapping_color(t_fract *fract, unsigned char *ptr, int x, int color)
{
	int		opp;
	int 		dec;
	//int	a = 0x11223344;
	int	endian;
	//int	local_endian;
	       
	endian = fract->image_info.endian;
	//local_endian = 0;
	//if (((unsigned char *)&a)[0] == 0x11)
		//local_endian = 1;
	opp = fract->image_info.bpp/8;
	dec = opp;
	//printf("dec=%d, opp=%d, x=%d\n", dec, opp, x);
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
}

void	loop_xy(t_fract *fract, int (*get_color)(t_fract *, t_point))
{
	unsigned char*	ptr;
	int		color;
	t_point		point;

	point.y = fract->w_height;
	while (point.y--)
	{
		//ptr = fract->image_info.addr + fract->image_info.sl * (fract->w_height - point.y - 1);
		ptr = fract->image_info.addr + fract->image_info.sl * (point.y);
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
	//int	bpp1;
	//int	sl1;
	//int	endian1;

	fract->diversion_count = 0;
	fract->near_diversion_count = 0;
	/*
	if (!(fract->image_info.image = mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT)))
	{
		fract->error = MEMORY_ERROR;
		ft_printf("can't allocat memory\n");
		exit(1);
	}
	*/
	fract->image_info.addr = mlx_get_data_addr(fract->image_info.image, &fract->image_info.bpp, 
			&fract->image_info.sl, &fract->image_info.endian);
	//mapping_address(fract);
	fract->get_image(fract);
	float tmp_ratio;
	tmp_ratio = 0;
	if (fract->diversion_count > 0)
		tmp_ratio = (float)(100 * fract->near_diversion_count) / fract->diversion_count;
	if (tmp_ratio >= DIVERSION_COUNT_UP_THORESHOLD)
		fract->iteration_max += 2 + (tmp_ratio * 10);
	else if ((tmp_ratio < DIVERSION_COUNT_DOWN_THORESHOLD) && (fract->iteration_max > INTERATION_INIT) && fract->zoom_count > 0)
	{
		fract->iteration_max -= (fract->iteration_max - INTERATION_INIT)/fract->zoom_count ;
	}

	//printf("bpp1=%d, sl1=%d, endian1=%d,fract->diversion_count=%d,fract->near_diversion_count=%d ,tmp_ratio=%lf\n",fract->image_info.bpp, fract->image_info.sl, fract->image_info.endian,fract->diversion_count, fract->near_diversion_count,tmp_ratio);
	//if (diversion_count > )
	//mlx_put_image_to_window(fract->mlx, fract->window, fract->image_info.image, 80, 80);
	//mlx_string_put(fract->mlx, fract->window, fract->w_width * 0.5 , fract->w_height * 0.5, 0xffffffff, "Calculating2"   );
	//mlx_string_put(fract->mlx, fract->window, fract->w_width * 0.75 , fract->w_height * 0.75, 0x00, "Calculating3"   );
	return (true);

}

int	update_image(t_fract *fract)
{
	if (!fract->update_image_flag)
		return (false);
	if (fract->create_image_flag)
		create_image(fract);
	mlx_put_image_to_window(fract->mlx, fract->window, fract->image_info.image, fract->offset.x, fract->offset.y);
	fract->update_image_flag = false;
	fract->create_image_flag = false;
	return (true);
}
