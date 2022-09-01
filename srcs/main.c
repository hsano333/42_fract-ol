/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:54:57 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 20:42:23 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fract.h"
#include "ft_printf.h"
#include "image.h"

int	main(int argc, char **argv)
{
	t_fract	fract;

	init(argc, argv, &fract);
	create_image(&fract);
	if (fract.error != NO_ERROR)
		return (false);
	mlx_loop(fract.mlx);
	return (0);
}
