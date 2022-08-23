/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 05:38:17 by hsano             #+#    #+#             */
/*   Updated: 2022/08/23 07:32:01 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"

void	set_step(t_fract *fract)
{
	if (fract->w_width != 0)
		fract->step.r = (R_END - R_START) / fract->w_width;
	if (fract->w_height != 0)
		fract->step.i = (I_END - I_START) / fract->w_height;

}

/*
t_ipoint	convert_dpoint_to_ipoint(t_fract *fract, t_point point)
{
	t_ipoint ipoint;
	ipoint.z = 
}

*/
