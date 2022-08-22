/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 01:31:35 by hsano             #+#    #+#             */
/*   Updated: 2022/08/22 18:44:50 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	mapping_color(t_fract *fract, unsigned char *ptr, int x, int color)
{
	int		opp;
	int 		dec;
	int	a = 0x11223344;
	int	endian;
	int	local_endian;
	       
	endian = fract->image_info.endian;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1;
	else
		local_endian = 0;
	opp = fract->image_info.bpp/8;
	dec = opp;
	while (dec--)
	{
	    if (endian && endian==local_endian)
		  *(ptr+x*opp+dec) = ((unsigned char *)(&color))[4-opp+dec];
	    else if (!endian && endian==local_endian)
		  *(ptr+x*opp+dec) = ((unsigned char *)(&color))[dec];
	    else if (endian && endian != local_endian)
		  *(ptr+x*opp+dec) = ((unsigned char *)(&color))[opp-1-dec];
	    else if (!endian && endian != local_endian)
		  *(ptr+x*opp+dec) = ((unsigned char *)(&color))[3-dec];
	}
}

void	mapping_address( t_fract *fract)
{

	unsigned char*	ptr;
	int		color;
	int	x;
	int	y;

	y = fract->w_height;

	//color = (255 << 16) + (255 << 8) + 255;
	//color = 0;
	//
	
	while (y--)
	{
		ptr = fract->image_info.addr + fract->image_info.sl * y;
		x = fract->w_width;
		while (x--)
		{

			color = mlx_get_color_value(fract->mlx, fract->get_color(fract, x, y));
			mapping_color(fract, ptr, x, color);
		}
	}


	//*ptr = (unsigned char *)(&color2);

}

int	create_image(t_fract *fract)
{
	//int	bpp1;
	//int	sl1;
	//int	endian1;

	if (fract->image_info.image)
		mlx_destroy_image(fract->mlx, fract->image_info.image);
	if (!(fract->image_info.image = mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT)))
	{
		fract->error = MEMORY_ERROR;
		ft_printf("can't allocat memory\n");
		exit(1);
	}
	fract->image_info.addr = mlx_get_data_addr(fract->image_info.image, &fract->image_info.bpp, 
			&fract->image_info.sl, &fract->image_info.endian);
	ft_printf("bpp1=%d, sl1=%d, endian1=%d\n",fract->image_info.bpp, fract->image_info.sl, fract->image_info.endian);
	mapping_address(fract);
	mlx_put_image_to_window(fract->mlx, fract->window, fract->image_info.image, 80, 80);
	return (true);

}



