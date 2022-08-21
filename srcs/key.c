/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 09:11:31 by hsano             #+#    #+#             */
/*   Updated: 2022/08/21 18:43:41 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "key.h"
#include "ft_printf.h"

int	hook_key(int key,void *p)
{

	if (key == ARROW_LEFT)
		ft_printf("ARROW_LEFT key : %p\n",p);
	else if (key == ARROW_UP)
		ft_printf("ARROW_UP key : %p\n",p);
	else if (key == ARROW_RIGHT)
		ft_printf("ARROW_RIGHT key : %p\n",p);
	else if (key == ARROW_DOWN)
		ft_printf("ARROW_DOWN key : %p\n",p);
	else
		ft_printf("other key :%d  %p\n",key,p);
	return (true);
}
