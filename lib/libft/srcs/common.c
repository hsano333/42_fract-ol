/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:39:43 by hsano             #+#    #+#             */
/*   Updated: 2022/08/06 23:12:25 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	clear_conversion(t_conversion *node)
{
	free(node);
}
