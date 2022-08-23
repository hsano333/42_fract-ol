/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:37:22 by hsano             #+#    #+#             */
/*   Updated: 2022/08/23 15:24:26 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"
#include "mouse.h"
#include "ft_printf.h"

int	detect_move(int x, int y, void *p)
{
	if (p != NULL)
		ft_printf("Mouse moving in Win3, at %dx%d.%p\n",x,y,p);
	else
		ft_printf("Mouse moving in Win3, at %dx%d\n",x,y);
	return (true);
}


void	scroll_action(t_fract *fract, int x, int y,  int zoom_mode)
{
	float ratio;
	t_point	point;
	ratio = ZOOM_RATIO;
	if (zoom_mode == SCROLL_UP)
		ratio = 1/ratio;
	point.x = x;
	point.y = fract->w_height - y - 1;
	update_display_area(fract, point, ratio);
	create_image(fract);
	mlx_put_image_to_window(fract->mlx, fract->window, fract->image_info.image, 0, 0);
}


int	hook_mouse(int key, int x, int y, void *fract)
{
	if (key == LEFT)
		ft_printf("Left Click event x=%d,y=%d,,%pfract new win\n",x,y,fract);
	else if (key == WHEEL)
		ft_printf("Wheel Click event x=%d,y=%d,,%pfract new win\n",x,y,fract);
	else if (key == RIGHT)
		ft_printf("Right Click event x=%d,y=%d,,%pfract new win\n",x,y,fract);
	else if (key == SCROLL_UP)
		scroll_action(fract, x, y, SCROLL_UP);
		//ft_printf("SCROOL UP event x=%d,y=%d,,%pfract new win\n",x,y,fract);
	else if (key == SCROLL_DOWN)
		scroll_action(fract, x, y, SCROLL_DOWN);
		//ft_printf("SCROOL DOWN event x=%d,y=%d,,%pfract new win\n",x,y,fract);
	//if (fract != NULL)
		//ft_printf("Mouse event -x=%d,y=%d,button=%d,,%pfract new win\n",x,y,button,fract);
	//else
		//ft_printf("Mouse event -x=%d,y=%d,button=%d,,fract new win\n",x,y,button);
	return (true);
}
