/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 05:51:05 by hsano             #+#    #+#             */
/*   Updated: 2022/08/30 06:16:00 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fract.h>

t_ipoint	transform_ri(t_fract *fract, int x, int y)
{
	t_ipoint point;
	point.r = fract->i_area.r_begin + fract->step.r * x;
	point.i = fract->i_area.i_begin + fract->step.i * y;

	return (point);
}
