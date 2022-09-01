/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:37:22 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 06:59:16 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"
#include "mouse.h"
#include "zoom.h"
#include "ft_printf.h"
#include "libft_str.h"

int	hook_mouse(int key, int x, int y, void *fract)
{
	if (key == WHEEL)
		((t_fract *)fract)->lock = false;
	if (((t_fract *)fract)->lock)
		return (false);
	if (key == SCROLL_UP)
	{
		zoom_action(fract, x, y, ZOOM_IN);
		((t_fract *)fract)->zoom_count++;
		((t_fract *)fract)->lock = true;
	}
	else if (key == SCROLL_DOWN)
	{
		zoom_action(fract, x, y, ZOOM_OUT);
		((t_fract *)fract)->zoom_count--;
		((t_fract *)fract)->lock = true;
	}
	return (true);
}
