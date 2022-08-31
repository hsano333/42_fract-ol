/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:50:26 by hsano             #+#    #+#             */
/*   Updated: 2022/08/30 21:31:01 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	calc_color6(int n, int loop_max, int diverse_flag)
{
	int	color;
	//int flag[3];
	
	//flag[0] = 0;
	//flag[1] = 0;
	//flag[2] = 0;
	color = loop_max;
	color = n;
	color = (255 * n) / loop_max;
	/*
	if (0b11100000 > color)
		flag[0] = color;
	else if (0b00100000 > color)
		flag[1] = color;
	else 
		flag[2] = color;
	*/
	if (diverse_flag)
		color = (255 << 16) + (n * 7 << 8) + (0);
	else
		color = 0;
	return (color);
}
