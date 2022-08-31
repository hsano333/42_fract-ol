/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:55:18 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 07:00:39 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include	"mlx_int.h"
#include "libft_isto.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "libft_mem.h"
#include "image.h"
#include "color.h"

static int	set_fract(char **argv, t_fract *fract)
{
	char	*str;
	int	argv_size;
	size_t	i;

	str = argv[1];
	i = -1;
	argv_size = ft_printf(str);
	while (str[i++])
		str[i] = ft_tolower(str[i]);
	fract->fract_set = INVALID;
	if (!ft_strncmp(argv[1], "mandelbrot", ft_strlen("mandelbrot")) 
			|| !ft_strncmp(argv[1], "m", argv_size) || !ft_strncmp(argv[1], "1", argv_size))
	{
		fract->fract_set = MANDELBROT;
		fract->get_image = (int (*)())get_mandelbrot_image;
	}
	else if (!ft_strncmp(argv[1], "julia", ft_strlen("julia")) 
			|| !ft_strncmp(argv[1], "j", argv_size) || !ft_strncmp(argv[1], "2", argv_size))
	{
		fract->fract_set = JULIA;
		fract->get_image = (int (*)())get_julia_image;
	}
	else if (!ft_strncmp(argv[1], "burning_ship", ft_strlen("burning_ship")) 
			|| !ft_strncmp(argv[1], "b", argv_size) || !ft_strncmp(argv[1], "3", argv_size))
	{
		fract->fract_set = BURNING_SHIP;
		fract->get_image = (int (*)())get_burning_ship_image;
	}
	else if (!ft_strncmp(argv[1], "gasket", ft_strlen("gasket")) 
			|| !ft_strncmp(argv[1], "g", argv_size) || !ft_strncmp(argv[1], "4", argv_size))
	{
		fract->fract_set = GASKET;
		fract->get_image = (int (*)())get_gasket_image;
	}
	else
		return (false);
	return (true);
}

static int	set_option(int argc, char **argv, t_fract *fract)
{
	int	error;

	if (argc <= 2)
		return (true);
	fract->c.r = (long double)ft_atod(argv[2], &error);
	if (error == true || fract->c.r > 2 || fract->c.r < -2)
		return (false);
		//fract->error = ARGV_ERROR;
	if (argc == 3)
		return (true);
	fract->c.i = (long double)ft_atod(argv[3], &error);
	if (error == true || fract->c.i > 2 || fract->c.i < -2)
		return (false);
		//fract->error = ARGV_ERROR;
	return (true);
}
int	expose_win(void *p)
{
	t_fract *fract;
	fract = p;
	ft_printf("expose_test No.1 %p\n", fract);
	//mlx_put_image_to_window(mlx,win1,im3,0,0);
	//mlx_put_image_to_window(fract->mlx, fract->window, fract->image_info.image, 80, 80);
	mlx_put_image_to_window(fract->mlx, fract->window, fract->image_info.image, fract->offset.x, fract->offset.y);
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
	fract->image_info.image = mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	fract->image_backup = mlx_new_image(fract->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!fract->image_info.image || !fract->image_backup)
	{
		fract->error = MEMORY_ERROR;
		close_fract(fract);
		//return (false);
		//ft_printf("can't allocat memory\n");
		//exit(1);
	}
	mlx_expose_hook(fract->window, expose_win, fract);
	ft_printf("befrore mlx_mouse_hook \n");
	mlx_mouse_hook(fract->window, hook_mouse, fract);
	//mlx_disble_mouse_hook(fract->window, hook_mouse, fract);
	ft_printf("after mlx_mouse_hook \n");
	//printf("ButtonPress=%d, ButtonPressMask",ButtonPress,ButtonPressMask);
	mlx_key_hook(fract->window, hook_key, fract);
	mlx_hook(fract->window, ON_DESTROY, NoEventMask, close_fract, fract);
	//mlx_hook(fract->window, 34, NoEventMask,test_number ,fract);
	mlx_hook(fract->window, ON_EXPOSE, NoEventMask, unlock, fract);
	mlx_loop_hook(fract->mlx, update_image, fract);
	return (true);
}

void	set_init_value(t_fract * fract)
{
	int	a = 0x11223344;

	fract->error = NO_ERROR;
	fract->speed_thoreshold = SPEED_THRESHOLD;
	fract->w_width = IMAGE_WIDTH;
	fract->w_height = IMAGE_HEIGHT;
	fract->calc_color = (int (*)())calc_color1;
	if (fract->fract_set == BURNING_SHIP)
	{
		fract->i_area.r_begin = -1.2;
		fract->i_area.r_last = 1.2;
		fract->i_area.i_begin = -1;
		fract->i_area.i_last = 1;
		fract->iteration_max = INTERATION_INIT;
		fract->calc_color = (int (*)())calc_color6;
	}
	else
	{
		fract->i_area.r_begin = R_START;
		fract->i_area.r_last = R_END;
		fract->i_area.i_begin = I_START;
		fract->i_area.i_last = I_END;
		fract->iteration_max = INTERATION_INIT;
	}
	fract->i_area_base = fract->i_area;
	fract->c.r = -0.12;
	fract->c.i = 0.74;
	fract->offset.x = (W_WIDTH - IMAGE_WIDTH) / 4;
	fract->offset.y = (W_HEIGHT - IMAGE_HEIGHT) / 4;
	fract->offset.y = (W_HEIGHT - IMAGE_HEIGHT) / 4;
	fract->defalut_color = ((255 << 16) + (255 << 8) + 255);
	set_step(fract);
	fract->local_endian = 0;
	if (((unsigned char *)&a)[0] == 0x11)
		fract->local_endian = 1;
}

void	invalid_parameter(int argc, t_fract *fract)
{
	if (argc <= 2)
		ft_printf("parameters are missing\n");
	if (fract->fract_set == INVALID)
		ft_printf("First parameter is invalid\n");
	ft_printf("usage: fract fract_set [init_r] [init_i]\n");
	ft_printf("fract_set:\n");
	ft_printf(" 	\"m\" , \"1\" , \"mandelbrot\"		: display Mandelbrot set\n");
	ft_printf(" 	\"j\" , \"2\" , \"julia\"		: display julia set\n");
	ft_printf(" 	\"b\" , \"3\" , \"burning_ship\"	: display burning-ship set\n");
	ft_printf(" 	\"g\" , \"4\" , \"gasket\"		: display gasket set\n");
	ft_printf("init_r=[-]NUM:init_r is real number. -2 <= init_r and init_r <= 2. It is necessary for Julia set but not for others. \n");
	ft_printf("init_i=[-]NUM:init_i is real number. -2 <= init_i and init_i <= 2. It is necessary for Julia set but not for others. \n");
	ft_printf("\nsample11: fract m \n");
	ft_printf("sample12: fract julia -0.12 0.74 \n");
	ft_printf("sample13: fract b \n");
	ft_printf("sample13: fract g \n");
	exit(1);
}

void	init(int argc, char** argv, t_fract *fract)
{
	int is_valid_param;

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
