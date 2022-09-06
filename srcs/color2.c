/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:50:26 by hsano             #+#    #+#             */
/*   Updated: 2022/09/06 08:01:15 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	calc_color6(int n, int loop_max, int diverse_flag)
{
	int	color;
	int	flag[3];

	color = loop_max;
	color = n;
	color = (255 * n) / loop_max;
	if (color == 0)
		flag[0] = 255;
	else if (color < 30 && color != 0)
	{
		flag[0] = 255 - n;
		if (flag[0] > 245)
			flag[0] = 255;
	}
	flag[1] = ((n * 255) / loop_max);
	if (flag[1] < 5)
		flag[1] = 255 - n;
	else if (flag[1] < 35)
		flag[1] *= 7;
	else
		flag[1] = 10;
	color = 0;
	if (diverse_flag)
		color = (flag[0] << 16) + (flag[1] << 8) + (0);
	return (color);
}

int	calc_color7(int n, int loop_max, int diverse_flag)
{
	int	color;

	color = loop_max;
	color = diverse_flag;
	color = (255 * n / 32 << 16) + (0 << 8) + ((n * 255) / 4);
	return (color);
}

int	calc_color8(int n, int loop_max, int diverse_flag)
{
	int	color;
	int	tmp;

	tmp = (255 * n) / loop_max;
	if (tmp > 255)
		tmp = 255;
	if (diverse_flag)
		color = ((255 - tmp) << 16) + (tmp / 2 << 8) + (tmp);
	else
		color = 0;
	return (color);
}
