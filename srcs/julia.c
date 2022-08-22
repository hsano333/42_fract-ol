/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:30:26 by hsano             #+#    #+#             */
/*   Updated: 2022/08/22 17:59:57 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int	get_julia_color(t_fract *fract, int x, int y)
{
	int w;
	int	color;

	w = fract->w_width;
	color = (y*255)/w+((((w-x)*255)/w)<<16);
	//ft_printf("julia x:%d, y:%d  ,\n", x, y);
	return (color);
}
