/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:54:57 by hsano             #+#    #+#             */
/*   Updated: 2022/08/21 15:52:34 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fract.h"
#include "ft_printf.h"

int main(int argc, char** argv)
{
	t_fract	fract;

	init(argc, argv, &fract);
	mlx_loop(fract.mlx);
	return (0);
}
