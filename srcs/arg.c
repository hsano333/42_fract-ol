/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:58:38 by hsano             #+#    #+#             */
/*   Updated: 2022/09/02 17:21:43 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"
#include "image.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "libft_isto.h"
#include <errno.h>

int	set_fract(char **argv, t_fract *fract)
{
	int		len;
	char	*str;
	size_t	i;

	str = argv[1];
	i = -1;
	len = ft_strlen(str);
	while (str[i++])
		str[i] = ft_tolower(str[i]);
	fract->fract_set = INVALID;
	if (!ft_strncmp(argv[1], "mandelbrot", ft_strlen("mandelbrot")) \
			|| !ft_strncmp(argv[1], "m", len) || !ft_strncmp(argv[1], "1", len))
		fract->init = (void *)init_mandelbrot;
	else if (!ft_strncmp(argv[1], "julia", ft_strlen("julia")) \
			|| !ft_strncmp(argv[1], "j", len) || !ft_strncmp(argv[1], "2", len))
		fract->init = (void *)init_julia;
	else if (!ft_strncmp(argv[1], "burning_ship", ft_strlen("burning_ship")) \
			|| !ft_strncmp(argv[1], "b", len) || !ft_strncmp(argv[1], "3", len))
		fract->init = (void *)init_burning_ship;
	else if (!ft_strncmp(argv[1], "gasket", ft_strlen("gasket")) \
			|| !ft_strncmp(argv[1], "g", len) || !ft_strncmp(argv[1], "4", len))
		fract->init = (void *)init_gasket;
	else
		return (false);
	return (true);
}

void	invalid_parameter(int argc, t_fract *fract)
{
	errno = 22;
	if (argc < 2)
		ft_printf("\n%s:%s\n", strerror(errno), "parameters are missing\n");
	else if (fract->fract_set == INVALID)
		ft_printf("\n%s:%s\n", strerror(errno), "First parameter is invalid\n\n");
	ft_printf("usage: fract fract_set [init_r] [init_i]\n");
	ft_printf("fract_set:\n");
	ft_printf(" 	\"m\" , \"1\" , \"mandelbrot\"	: display Mandelbrot set\n");
	ft_printf(" 	\"j\" , \"2\" , \"julia\"		: display julia set\n");
	ft_printf(" 	\"b\" , \"3\" , \"burning_ship\"	: display burning-ship set\n");
	ft_printf(" 	\"g\" , \"4\" , \"gasket\"		: display gasket set\n");
	ft_printf("init_r=[-]NUM:init_r is real number. -2 <= init_r and ");
	ft_printf("init_r <= 2. It's necessary for Julia set but not for others\n");
	ft_printf("init_i=[-]NUM:init_i is real number. -2 <= init_i and ");
	ft_printf("init_i <= 2. It's necessary for Julia set but not for others\n");
	ft_printf("\nsample11: fract m \n");
	ft_printf("sample12: fract julia -0.12 0.74 \n");
	ft_printf("sample13: fract b \n");
	ft_printf("sample14: fract g \n");
	exit(1);
}

static int	check_word(char *str)
{
	size_t	i;
	size_t	dot_cnt;

	i = 0;
	dot_cnt = 0;


	if (!((ft_isdigit(str[i]) || str[i] == '-')))
		return (false);
	while (str[++i])
	{
		if (ft_isdigit(str[i]))
			continue ;
		else if (str[i] == '.')
		{
			dot_cnt++;
			continue ;
		}
		else
			return (false);
	}
	if (dot_cnt >= 2)
		return (false);
	return (true);
}

int	set_option(int argc, char **argv, t_fract *fract)
{
	int		error;

	if (argc == 2)
		return (true);
	else if (argc == 3)
		return (false);
	else if (argc >= 5)
		return (false);
	if (!check_word(argv[2]))
		return (false);
	if (!check_word(argv[3]))
		return (false);
	fract->c.r = (long double)ft_atod(argv[2], &error);
	if (error == true || fract->c.r > 2 || fract->c.r < -2)
		return (false);
	fract->c.i = (long double)ft_atod(argv[3], &error);
	if (error == true || fract->c.i > 2 || fract->c.i < -2)
		return (false);
	return (true);
}
