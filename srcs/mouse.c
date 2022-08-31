/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:37:22 by hsano             #+#    #+#             */
/*   Updated: 2022/08/30 20:01:36 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"
#include "mouse.h"
#include "zoom.h"
#include "ft_printf.h"
#include "libft_str.h"

int	detect_move(int x, int y, void *p)
{
	if (p != NULL)
		ft_printf("Mouse moving in Win3, at %dx%d.%p\n",x,y,p);
	else
		ft_printf("Mouse moving in Win3, at %dx%d\n",x,y);
	return (true);
}

int	hook_mouse(int key, int x, int y, void *fract)
{
	if (key == WHEEL)
		((t_fract*)fract)->lock = false;
	//mlx_loop_end(((t_fract*)fract)->mlx);
	if (((t_fract*)fract)->lock)
		return (false);

	if (key == LEFT)
		ft_printf("Left Click event x=%d,y=%d,,%pfract new win\n",x,y,fract);
	else if (key == WHEEL)
		ft_printf("Wheel Click event x=%d,y=%d,,%pfract new win\n",x,y,fract);
	else if (key == RIGHT)
		ft_printf("Right Click event x=%d,y=%d,,%pfract new win\n",x,y,fract);
	else if (key == SCROLL_UP)
	{
		zoom_action(fract, x, y, ZOOM_IN);
		((t_fract*)fract)->zoom_count++;
		((t_fract*)fract)->lock = true;
	}
	else if (key == SCROLL_DOWN)
	{
		zoom_action(fract, x, y, ZOOM_OUT);
		((t_fract*)fract)->zoom_count--;
		((t_fract*)fract)->lock = true;
	}
	return (true);
}
