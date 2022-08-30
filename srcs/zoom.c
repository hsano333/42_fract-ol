/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:46:38 by hsano             #+#    #+#             */
/*   Updated: 2022/08/30 19:53:47 by hsano            ###   ########.fr       */
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
	//mlx_disble_mouse_hook(fract->window, hook_mouse, fract);
	//mlx_hook(fract->window, 3, ButtonPressMask, close_fract, fract);
	/*
	mlx_hook(fract->window, 3, ButtonPressMask, close_fract, fract);
	mlx_hook(fract->window, 4, ButtonPressMask, close_fract, fract);
	mlx_hook(fract->window, 5, ButtonPressMask, close_fract, fract);
	*/

	//mlx_put_image_to_window(fract->mlx, fract->window, fract->image_info.image, 0, 0);
	if (zoom_mode == ZOOM_IN)
		ratio = 1/ratio;
	point.x = x;
	point.y = fract->w_height - y - 1;
	offset.x = 0;
	offset.y = 0;
	tmp = (100 * (fract->i_area_base.r_last - fract->i_area_base.r_begin) / (fract->i_area.r_last - fract->i_area.r_begin) ) / ratio;
	//char *zoom_str2 = ft_itoa(100);
	//printf("%s\n", zoom_str2);
	ft_ltoa((long)(tmp / 100), zoom_str);
	printf("tmp=%ld\n",tmp);
	printf("test No.0 zoom:%ld, zoom:str=%s\n",tmp/100, zoom_str);
	ft_strlcat(zoom_str, ".", ft_strlen(zoom_str)+2);
	//ft_strlcat(zoom_str, ft_ltoa((long)(tmp % 100), zoom_str), ft_strlen(zoom_str)+1);
	//ft_strjoin(zoom_str, "abc");
	printf("test No.1 zoom:%ld, zoom:str=%s\n",tmp/100, zoom_str);
	//ft_join(zoom_str, 
	//ft_ltoa((long)(tmp % 100), &(zoom_str[ft_strlen(zoom_str)]));
	ft_ltoa((long)(tmp % 100), &(zoom_str[ft_strlen(zoom_str)]));
	printf("test No.2 zoom:%ld, zoom:str=%s\n",tmp/100, zoom_str);
	update_display_area(fract, point, ratio, offset);
	//create_image(fract);
	mlx_string_put(fract->mlx, fract->window, IMAGE_WIDTH * 0.5, IMAGE_HEIGHT * 0.5, 0xffffffff, "Calculating");
	mlx_string_put(fract->mlx, fract->window, IMAGE_WIDTH * 0.5, IMAGE_HEIGHT * 0.53, 0xffffffff, "ZOOM: ");
	//ft_strlcpy(zoom_str, , );
	mlx_string_put(fract->mlx, fract->window, IMAGE_WIDTH * 0.55, IMAGE_HEIGHT * 0.53, 0xffffffff, zoom_str);
	fract->update_image_flag = true;
	fract->create_image_flag = true;
}
