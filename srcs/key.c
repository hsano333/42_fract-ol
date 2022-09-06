/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 09:11:31 by hsano             #+#    #+#             */
/*   Updated: 2022/09/06 07:18:07 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "image.h"
#include "key.h"
#include "ft_printf.h"
#include "math.h"
#include "color.h"
#include "zoom.h"

void	reset_image(t_fract *fract)
{
	set_init_value(fract);
	create_image(fract);
	fract->offset.x = (W_WIDTH - IMAGE_WIDTH) / 4;
	fract->offset.y = (W_HEIGHT - IMAGE_HEIGHT) / 4;
	mlx_put_image_to_window(fract->mlx, fract->window, \
			fract->image_info.image, fract->offset.x, fract->offset.y);
}

void	update_over_offset(t_fract *fract)
{
	t_point	point;

	mlx_string_put(fract->mlx, fract->window, IMAGE_WIDTH * 0.5, \
				IMAGE_HEIGHT * 0.5, fract->defalut_color, "Calculating");
	point.x = W_WIDTH / 2;
	point.y = W_HEIGHT / 2;
	fract->offset.x -= (W_WIDTH - IMAGE_WIDTH) / 4;
	//fract->offset.y -= (W_HEIGHT - IMAGE_HEIGHT) / 4;
	fract->offset.y = fract->offset.y + ((W_HEIGHT - IMAGE_HEIGHT) / 4 )  ;
	update_display_area(fract, point, 1, fract->offset);
	fract->offset.x = (W_WIDTH - IMAGE_WIDTH) / 4;
	fract->offset.y = -(W_HEIGHT - IMAGE_HEIGHT) / 4;
	fract->create_image_flag = true;
}

void	update_offset(int key, t_fract *fract)
{
	if (key == ARROW_LEFT)
		fract->offset.x += MOVING_VALUE;
	else if (key == ARROW_UP)
		fract->offset.y -= MOVING_VALUE;
	else if (key == ARROW_RIGHT)
		fract->offset.x -= MOVING_VALUE;
	else if (key == ARROW_DOWN)
		fract->offset.y += MOVING_VALUE;
	if (fract->offset.x > 0 || fract->offset.x < (W_WIDTH - IMAGE_WIDTH) / 2 \
			|| fract->offset.y > 0 \
			|| fract->offset.y < (W_HEIGHT - IMAGE_HEIGHT) / 2)
	{
		update_over_offset(fract);
	}
	((t_fract *)fract)->lock = true;
	fract->update_image_flag = true;
}

void	set_calc_method(t_fract *fract)
{
	if (fract->calc_color == (int (*)())calc_color1)
		fract->calc_color = (int (*)())calc_color2;
	else if (fract->calc_color == (int (*)())calc_color2)
		fract->calc_color = (int (*)())calc_color3;
	else if (fract->calc_color == (int (*)())calc_color3)
		fract->calc_color = (int (*)())calc_color4;
	else if (fract->calc_color == (int (*)())calc_color4)
		fract->calc_color = (int (*)())calc_color5;
	else if (fract->calc_color == (int (*)())calc_color5)
		fract->calc_color = (int (*)())calc_color6;
	else if (fract->calc_color == (int (*)())calc_color6)
		fract->calc_color = (int (*)())calc_color7;
	else if (fract->calc_color == (int (*)())calc_color7)
		fract->calc_color = (int (*)())calc_color8;
	else if (fract->calc_color == (int (*)())calc_color8)
		fract->calc_color = (int (*)())calc_color1;
	fract->create_image_flag = true;
	((t_fract *)fract)->lock = true;
	fract->update_image_flag = true;
	fract->defalut_color = ((255 << 16) + (255 << 8) + 255);
	if (fract->calc_color == (int (*)())calc_color2
			|| fract->calc_color == (int (*)())calc_color3)
		fract->defalut_color = ((255 << 16) + (0 << 8) + 0);
}

int	hook_key(int key, void *fract)
{
	if (((t_fract *)fract)->lock)
		return (false);
	if (key == ARROW_LEFT || key == ARROW_RIGHT)
		update_offset(key, ((t_fract *)fract));
	else if (key == ARROW_UP || key == ARROW_DOWN)
		update_offset(key, ((t_fract *)fract));
	else if (key == C_KEY)
		set_calc_method(fract);
	else if (key == ESC)
		close_fract(fract);
	else if (key == R_KEY)
		reset_image(fract);
	else if (key == U_KEY)
		(((t_fract *)fract)->iteration_max)++;
	else if (key == I_KEY)
		zoom_action(fract, IMAGE_WIDTH / 2, IMAGE_HEIGHT / 2, ZOOM_IN);
	else if (key == O_KEY)
		zoom_action(fract, IMAGE_WIDTH / 2, IMAGE_HEIGHT / 2, ZOOM_OUT);
	return (true);
}
