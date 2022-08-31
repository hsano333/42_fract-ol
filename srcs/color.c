/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:50:26 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 23:47:17 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	calc_color1(int n, int loop_max, int diverse_flag)
{
	int	color;
	int	flag[3];

	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	color = loop_max;
	color = n;
	color = (255 * n) / loop_max;
	if (0b11100000 > color)
		flag[0] = color;
	else if (0b00100000 > color)
		flag[1] = color;
	else
		flag[2] = color;
	if (diverse_flag)
		color = (flag[0] << 16) + (flag[1] << 8) + (flag[2]);
	else
		color = 0;
	return (color);
}

int	calc_color2(int n, int loop_max, int diverse_flag)
{
	int	color;

	color = loop_max;
	color = n;
	if (diverse_flag)
		color = (255 << 16) + (255 << 8) + 255;
	else
		color = 0;
	return (color);
}

int	calc_color3(int n, int loop_max, int diverse_flag)
{
	int	color;

	color = loop_max;
	color = n;
	if (diverse_flag)
		color = (n << 16) + (n << 8) + n;
	else
		color = (n << 16) + (n << 8) + n;
	return (color);
}

int	calc_color4(int n, int loop_max, int diverse_flag)
{
	int	color;

	color = loop_max;
	color = n;
	n = (255 * n) / loop_max;
	if (diverse_flag)
		color = n * loop_max;
	else
		color = 0;
	return (color);
}

int	calc_color5(int n, int loop_max, int diverse_flag)
{
	int	color;
	int	flag[3];

	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	color = loop_max;
	color = n;
	color = (255 * n) / loop_max;
	if (0b11100000 > color)
		flag[0] = color;
	else if (0b00100000 > color)
		flag[1] = color;
	else
		flag[2] = color;
	if (diverse_flag)
		color = (flag[0] << 16) + (flag[1] << 8) + (flag[2]) * loop_max;
	else
		color = 0;
	return (color);
}
