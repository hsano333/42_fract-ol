/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:55:18 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 01:01:17 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "mlx_int.h"
#include "libft_isto.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "libft_mem.h"
#include "image.h"
#include "color.h"
#include "arg.h"

int	expose_win(void *p)
{
	t_fract	*fract;

	fract = p;
	mlx_put_image_to_window(fract->mlx, fract->window, \
		   	fract->image_info.image, fract->offset.x, fract->offset.y);
	return (true);
}

static int	init_mlx(t_fract *fract)
{
	fract->mlx = mlx_init();
	if (!fract->mlx)
		return (false);
	fract->window = mlx_new_window(fract->mlx, W_WIDTH, W_HEIGHT, "fractl-ol");
	if (!fract->window)
		return (false);
	fract->image_info.image = \
		mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!fract->image_info.image)
	{
		fract->error = MEMORY_ERROR;
		close_fract(fract);
	}
	mlx_expose_hook(fract->window, expose_win, fract);
	mlx_mouse_hook(fract->window, hook_mouse, fract);
	mlx_key_hook(fract->window, hook_key, fract);
	mlx_hook(fract->window, ON_DESTROY, NoEventMask, close_fract, fract);
	mlx_hook(fract->window, ON_EXPOSE, NoEventMask, unlock, fract);
	mlx_loop_hook(fract->mlx, update_image, fract);
	return (true);
}

void	init(int argc, char **argv, t_fract *fract)
{
	int	is_valid_param;

	is_valid_param = false;
	ft_memset(fract, 0, sizeof(t_fract));
	if (argc == 1)
		invalid_parameter(argc, fract);
	if (!set_fract(argv, fract))
		invalid_parameter(argc, fract);
	set_init_value(fract);
	is_valid_param = set_option(argc, argv, fract);
	if (is_valid_param == false)
		invalid_parameter(argc, fract);
	init_mlx(fract);
}
