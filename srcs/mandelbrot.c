/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:22:23 by hsano             #+#    #+#             */
/*   Updated: 2022/08/22 18:52:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int	get_mandelbrot_color(t_fract *fract, int x, int y)
{
	int color;
	int w = fract->w_width;
	int h = fract->w_height;
	color = (y*255)/h+((((w-x)*255)/w)<<16);
	color = (255 << 16) + (255 << 8) + 255;
	//ft_printf("mandelbrot x:%d, y:%d   width:%d\n", x, y, fract->w_width);
	return (color);
}
