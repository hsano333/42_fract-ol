/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:47:17 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 01:55:43 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOOM_H
# define ZOOM_H
# define ZOOM_IN 0
# define ZOOM_OUT 1

void	zoom_action(t_fract *fract, int x, int y, int zoom_mode);
#endif
