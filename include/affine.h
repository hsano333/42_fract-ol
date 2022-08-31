/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:46:03 by hsano             #+#    #+#             */
/*   Updated: 2022/08/30 20:26:26 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

typedef struct s_matrix {
	fract_type	a;
	fract_type	b;
	fract_type	c;
	fract_type	d;
	fract_type	e;
	fract_type	f;
}	t_matrix;

//void	affine(t_fract *fract, void *dest_addr, t_matrix matrix);
//void	affine(t_fract *fract, void *dest_addr, t_point offset,  t_matrix matrix);
t_area	affine(t_fract *fract, void *dest_addr, t_point offset,  t_matrix matrix);
