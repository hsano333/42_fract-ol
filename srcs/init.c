/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:55:18 by hsano             #+#    #+#             */
/*   Updated: 2022/08/21 15:44:09 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "libft_isto.h"
#include "libft_str.h"
#include "libft_mem.h"

static void	set_fract(char **argv, t_fract *fract)
{
	char	*str;
	size_t	i;

	str = argv[1];
	i = -1;
	while (str[i++])
		str[i] = ft_tolower(str[i]);
	if (ft_strncmp(argv[1], "julia", ft_strlen("julia")) 
			|| ft_strncmp(argv[1], "j", 1) || ft_strncmp(argv[1], "1", 1))
		fract->fract_set = MANDELBROT;
	else if (ft_strncmp(argv[1], "mandelbrot", ft_strlen("mandelbrot")) 
			|| ft_strncmp(argv[1], "m", 1) || ft_strncmp(argv[1], "2", 1))
		fract->fract_set = MANDELBROT;
}

static int	init_mlx(t_fract *fract)
{

	fract->mlx= mlx_init();
	if (!fract->mlx)
	{
		fract->error = MLX_INIT_ERROR;
		return (false);
	}
	fract->window = mlx_new_window(fract->mlx, W_HEIGHT, W_WIDTH, "fractl-ol");
	if (!fract->window)
	{
		fract->error = MLX_WINDOW_ERROR;
		return (false);
	}
	mlx_mouse_hook(fract->window, hook_mouse, 0);
	mlx_key_hook(fract->window, hook_key, 0);
	//mlx_hook(fract->window, MotionNotify, PointerMotionMask, detect_move, 0);
	//mlx_loop_hook(fract->mlx, detect_move, 0);
	return (true);
}

void	init(int argc, char** argv, t_fract *fract)
{
	//t_xvar	*xvar;

	printf("init No.1\n");
	ft_memset(fract, 0, sizeof(t_fract));
	printf("init No.2\n");
	fract->error = NO_ERROR;
	printf("init No.3\n");
	if (argc >= 2)
		set_fract(argv, fract);
	printf("init No.4\n");
	init_mlx(fract);
	printf("init No.5\n");

}
