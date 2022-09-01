/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:59:56 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 20:43:08 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_H
# define ARG_H

#include "fract.h"

int		set_fract(char **argv, t_fract *fract);
int		set_option(int argc, char **argv, t_fract *fract);
void	invalid_parameter(int argc, t_fract *fract);
#endif
