/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:41:17 by hsano             #+#    #+#             */
/*   Updated: 2022/08/23 12:23:16 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGESSS_H
#define IMAGESSS_H

#define R_START -2.1
#define R_END 0.8
#define I_START -1.2
#define I_END 1.2

#include "fract.h"

//void	draw_mandelbrot(void *image, t_fract *fract);
int	get_julia_color(t_fract *fract, t_point point);
int	get_mandelbrot_color(t_fract *fract, t_point point);
//void	draw_julia(void *image, t_fract *fract);
int	create_image(t_fract *fract);
void	set_step(t_fract *fract);

#endif
