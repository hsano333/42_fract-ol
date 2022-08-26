/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_common.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 06:52:45 by hsano             #+#    #+#             */
/*   Updated: 2022/08/26 07:40:03 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	remove_zero(const char *str, size_t i);
size_t	get_digit_len(const char *str, size_t i);
size_t	ft_iterative_power(long nb, long power);
size_t	get_start_index(const char *str, int *minus);
