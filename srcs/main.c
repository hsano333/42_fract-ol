/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:54:57 by hsano             #+#    #+#             */
/*   Updated: 2022/08/25 18:13:49 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fract.h"
#include "ft_printf.h"
#include "image.h"

#define	IM1_SX		242
#define	IM1_SY		242
int	bpp1;
int	sl1;
int	endian1;
char	*data1;


int main(int argc, char** argv)
{
	t_fract	fract;

	init(argc, argv, &fract);
	create_image(&fract);
	if (fract.error != NO_ERROR)
		return (false);
	mlx_loop(fract.mlx);
	return (0);
}
