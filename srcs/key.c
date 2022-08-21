/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 09:11:31 by hsano             #+#    #+#             */
/*   Updated: 2022/08/21 14:48:20 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "ft_printf.h"

int	hook_key(int key,void *p)
{

	if (p != NULL)
		ft_printf("Key in Win1 : %d:%p\n",key, p);
	else
		ft_printf("Key in Win1 : %d:\n",key);
	return (true);
}
