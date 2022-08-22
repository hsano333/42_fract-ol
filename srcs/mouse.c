/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:37:22 by hsano             #+#    #+#             */
/*   Updated: 2022/08/21 18:58:38 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
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



int	hook_mouse(int key, int x, int y, void*toto)
{
	if (key == LEFT)
		ft_printf("Left Click event x=%d,y=%d,,%ptoto new win\n",x,y,toto);
	else if (key == WHEEL)
		ft_printf("Wheel Click event x=%d,y=%d,,%ptoto new win\n",x,y,toto);
	else if (key == RIGHT)
		ft_printf("Right Click event x=%d,y=%d,,%ptoto new win\n",x,y,toto);
	else if (key == SCROLL_UP)
		ft_printf("SCROOL UP event x=%d,y=%d,,%ptoto new win\n",x,y,toto);
	else if (key == SCROLL_DOWN)
		ft_printf("SCROOL DOWN event x=%d,y=%d,,%ptoto new win\n",x,y,toto);
	//if (toto != NULL)
		//ft_printf("Mouse event -x=%d,y=%d,button=%d,,%ptoto new win\n",x,y,button,toto);
	//else
		//ft_printf("Mouse event -x=%d,y=%d,button=%d,,toto new win\n",x,y,button);
	return (true);
}
