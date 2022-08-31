/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:46:03 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 02:11:20 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFFINE_H
# define AFFINE_H
# include "fract.h"

typedef struct s_matrix {
	t_fract_type	a;
	t_fract_type	b;
	t_fract_type	c;
	t_fract_type	d;
	t_fract_type	e;
	t_fract_type	f;
}	t_matrix;

t_area	affine(t_fract *fract, void *dest_addr \
		, t_point offset, t_matrix matrix);
#endif
