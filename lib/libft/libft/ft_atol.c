/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 07:10:36 by hsano             #+#    #+#             */
/*   Updated: 2022/08/26 08:46:20 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_common.h"

long	ft_atol(const char *str, int *long_over_flag)
{
	int	minus;
	size_t	len;
	size_t	i;
	size_t	sum;
	size_t	a;

	i = remove_zero(str, get_start_index(str, &minus));
	sum = 0;
	len = get_digit_len(str, i);
	a = ft_iterative_power(10, len - 1);
	*long_over_flag = true;
	if (a == LONG_MAX || LONG_MAX/a < (str[i] - '0'))
		return (0);
	while (a > 0)
	{
		sum += (str[i++] - '0') * a;
		if (sum < (str[i -1] - '0') * a || sum > LONG_MAX + 1UL)
			return (0);
		a /= 10;
	}
	if (minus == 1 && sum == LONG_MAX + 1UL)
		return (0);
	*long_over_flag = false;
	return ((long)(sum * minus));
}
