/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:55:18 by hsano             #+#    #+#             */
/*   Updated: 2022/08/23 11:25:54 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "libft_isto.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "libft_mem.h"
#include "image.h"

static void	set_fract(char **argv, t_fract *fract)
{
	char	*str;
	size_t	i;

	str = argv[1];
	i = -1;
	while (str[i++])
		str[i] = ft_tolower(str[i]);
	if (!ft_strncmp(argv[1], "julia", ft_strlen("julia")) 
			|| !ft_strncmp(argv[1], "j", 1) || !ft_strncmp(argv[1], "1", 1))
	{
		fract->fract_set = JULIA;
		fract->get_color = (int (*)())get_julia_color;
	}
	else if (!ft_strncmp(argv[1], "mandelbrot", ft_strlen("mandelbrot")) 
			|| !ft_strncmp(argv[1], "m", 1) || !ft_strncmp(argv[1], "2", 1))
	{
		fract->fract_set = MANDELBROT;
		fract->get_color = (int (*)())get_mandelbrot_color;
	}
}

static int	set_option(int argc, char **argv, t_fract *fract)
{
	int	error;

	if (argc <= 2)
		return (true);
	fract->speed_thoreshold = ft_atoi(argv[3], &error);
	if (fract->speed_thoreshold <= 0)
		fract->error = ARGV_ERROR;
	if (argc == 3)
		return (true);
	fract->iteration_max = ft_atoi(argv[4], &error);
	if (fract->iteration_max <= 0)
		fract->error = ARGV_ERROR;

	return (true);
}

static int	init_mlx(t_fract *fract)
{

	fract->mlx= mlx_init();
	if (!fract->mlx)
	{
		fract->error = MLX_INIT_ERROR;
		return (false);
	}
	fract->window = mlx_new_window(fract->mlx, W_WIDTH, W_HEIGHT, "fractl-ol");
	if (!fract->window)
	{
		fract->error = MLX_WINDOW_ERROR;
		return (false);
	}
	mlx_mouse_hook(fract->window, hook_mouse, 0);
	mlx_key_hook(fract->window, hook_key, 0);
	return (true);
}

void	set_const_value(t_fract * fract)
{
	fract->error = NO_ERROR;
	fract->speed_thoreshold = SPEED_THRESHOLD;
	fract->iteration_max = INTERATION_MAX;
	fract->w_width = W_WIDTH;
	fract->w_height = W_HEIGHT;
	fract->i_area.r_begin = R_START;
	fract->i_area.r_last = R_END;
	fract->i_area.i_begin = I_START;
	fract->i_area.i_last = I_END;
	fract->c.r = -0.12;
	fract->c.i = 0.74;
	//fract->c.r = 0.25;
	//fract->c.i = 0;
	set_step(fract);
}

void	init(int argc, char** argv, t_fract *fract)
{
	ft_memset(fract, 0, sizeof(t_fract));
	set_const_value(fract);
	if (argc >= 2)
		set_fract(argv, fract);
	set_option(argc, argv, fract);
	init_mlx(fract);

}
