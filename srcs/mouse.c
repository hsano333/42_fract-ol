/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:37:22 by hsano             #+#    #+#             */
/*   Updated: 2022/08/21 14:47:58 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "ft_printf.h"

int	detect_move(int x,int y, void *p)
{
	if (p != NULL)
		ft_printf("Mouse moving in Win3, at %dx%d.%p\n",x,y,p);
	else
		ft_printf("Mouse moving in Win3, at %dx%d\n",x,y);
	return (true);
}

int	hook_mouse(int x,int y,int button,void*toto)
{
	if (toto != NULL)
		ft_printf("Mouse event -x=%d,y=%d,button=%d,,%ptoto new win\n",x,y,button,toto);
	else
		ft_printf("Mouse event -x=%d,y=%d,button=%d,,toto new win\n",x,y,button);
	return (true);
}
