/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:46:03 by hsano             #+#    #+#             */
/*   Updated: 2022/08/29 18:23:22 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

typedef struct s_matrix {
	double	a;
	double	b;
	double	c;
	double	d;
	double	e;
	double	f;
}	t_matrix;

//void	affine(t_fract *fract, void *dest_addr, t_matrix matrix);
//void	affine(t_fract *fract, void *dest_addr, t_point offset,  t_matrix matrix);
t_point	affine(t_fract *fract, void *dest_addr, t_point offset,  t_matrix matrix);
