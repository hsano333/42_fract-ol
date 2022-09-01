/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:46:38 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 13:32:46 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"
#include "zoom.h"
#include "libft_str.h"

void	put_zoom_message(t_fract *fract)
{
	char	zoom_str[100];
	long	tmp;

	tmp = (long)(fract->zoom_ratio * 100);
	ft_ltoa((long)(tmp / 100), zoom_str);
	ft_strlcat(zoom_str, ".", ft_strlen(zoom_str) + 2);
	ft_ltoa((long)(tmp % 100), &(zoom_str[ft_strlen(zoom_str)]));
	mlx_string_put(fract->mlx, fract->window, \
			IMAGE_WIDTH * 0.5, IMAGE_HEIGHT * 0.5, fract->defalut_color, "Calculating");
	mlx_string_put(fract->mlx, fract->window, \
		   	IMAGE_WIDTH * 0.5, IMAGE_HEIGHT * 0.53, fract->defalut_color, "ZOOM: ");
	mlx_string_put(fract->mlx, fract->window, \
			IMAGE_WIDTH * 0.55, IMAGE_HEIGHT * 0.53, fract->defalut_color, zoom_str);
}

void	zoom_action(t_fract *fract, int x, int y, int zoom_mode)
{
	float	ratio;
	t_point	point;
	t_point	offset;
	t_iarea	tmp_area;

	ratio = ZOOM_RATIO;
	if (zoom_mode == ZOOM_IN)
		ratio = 1 / ratio;
	point.x = x;
	point.y = y;
	offset.x = 0;
	offset.y = 0;
	tmp_area = fract->i_area_base;
	fract->zoom_ratio = ((tmp_area.r_last - tmp_area.r_begin) \
			/ (fract->i_area.r_last - fract->i_area.r_begin)) / ratio;
	update_display_area(fract, point, ratio, offset);
	fract->update_image_flag = true;
	fract->create_image_flag = true;
	put_zoom_message(fract);
}
