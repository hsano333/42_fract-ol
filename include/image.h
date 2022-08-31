/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:41:17 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 07:08:03 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGESSS_H
#define IMAGESSS_H

#define R_START -2.1
#define R_END 0.8
#define I_START -1.2
#define I_END 1.2
#define ZOOM_SCALE 2
#define ZOOM_RATIO 1.2


#include "fract.h"
#include "float.h"

//void	draw_mandelbrot(void *image, t_fract *fract);
//int	get_julia_color(t_fract *fract, t_point point);
//int	get_mandelbrot_color(t_fract *fract, t_point point);
//int	get_gasket_color(t_fract *fract, t_point w_point);
void	init_mandelbrot(t_fract *fract);
void	init_julia(t_fract *fract);
void	init_burning_ship(t_fract *fract);
void	init_gasket(t_fract *fract);
//int	get_julia_image(t_fract *fract);
//int	get_mandelbrot_image(t_fract *fract);
//int	get_gasket_image(t_fract *fract);
//int	get_koch_image(t_fract *fract);
//int	get_burning_ship_image(t_fract *fract);
//void	draw_julia(void *image, t_fract *fract);
int	create_image(t_fract *fract);
void	set_step(t_fract *fract);
int	update_image(t_fract *fract);
//int	get_color(t_fract *fract, int x, int y);
//int	is_black(t_fract *fract, int x, int y);
int	is_black(t_fract *fract, void *addr,  int x, int y);
void	loop_xy(t_fract *fract, int (*get_color)(t_fract*, t_point));
void	*copy_image(t_fract *fract);
void	overlapping_image(t_fract *fract, t_img *image, t_point offset);
void	clear_image(t_fract *fract, t_img *image);
t_ipoint	transform_ri(t_fract *fract, int x, int y);
#endif
