/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:46:38 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 09:21:36 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"
#include "zoom.h"
#include "libft_str.h"

void	zoom_action(t_fract *fract, int x, int y,  int zoom_mode)
{
	char	zoom_str[100];
	float ratio;
	long	tmp;
	t_point	point;
	t_point offset;
	ratio = ZOOM_RATIO;

	if (zoom_mode == ZOOM_IN)
		ratio = 1/ratio;
	point.x = x;
	point.y = y;
	//point.y = fract->w_height - y - 1;
	offset.x = 0;
	offset.y = 0;
	fract->zoom_ratio = ((fract->i_area_base.r_last - fract->i_area_base.r_begin) / (fract->i_area.r_last - fract->i_area.r_begin) ) / ratio;
	tmp = (long)(fract->zoom_ratio * 100);
	ft_ltoa((long)(tmp / 100), zoom_str);
	ft_strlcat(zoom_str, ".", ft_strlen(zoom_str)+2);
	ft_ltoa((long)(tmp % 100), &(zoom_str[ft_strlen(zoom_str)]));
	update_display_area(fract, point, ratio, offset);
	mlx_string_put(fract->mlx, fract->window, IMAGE_WIDTH * 0.5, IMAGE_HEIGHT * 0.5, 0xffffffff, "Calculating");
	mlx_string_put(fract->mlx, fract->window, IMAGE_WIDTH * 0.5, IMAGE_HEIGHT * 0.53, 0xffffffff, "ZOOM: ");
	mlx_string_put(fract->mlx, fract->window, IMAGE_WIDTH * 0.55, IMAGE_HEIGHT * 0.53, 0xffffffff, zoom_str);
	fract->update_image_flag = true;
	fract->create_image_flag = true;
}
