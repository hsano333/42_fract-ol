/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:41:17 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 07:05:41 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H
# define R_START -1.1
# define R_END 1.8
# define I_START -1.2
# define I_END 1.2
# define ZOOM_SCALE 2
# define ZOOM_RATIO 1.2

# include "fract.h"

int			create_image(t_fract *fract);
int			update_image(t_fract *fract);
int			is_black(t_fract *fract, void *addr, int x, int y);
void		init_mandelbrot(t_fract *fract);
void		init_julia(t_fract *fract);
void		init_burning_ship(t_fract *fract);
void		init_gasket(t_fract *fract);
void		loop_xy(t_fract *fract, int (*get_color)(t_fract*, t_point));
void		*copy_image(t_fract *fract);
void		overlapping_image(t_fract *fract, t_img *image, t_point offset);
void		clear_image(t_fract *fract, t_img *image);
void		set_init_value(t_fract *fract);
#endif
