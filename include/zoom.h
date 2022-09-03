/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:47:17 by hsano             #+#    #+#             */
/*   Updated: 2022/09/02 17:08:39 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOOM_H
# define ZOOM_H
# define ZOOM_IN 0
# define ZOOM_OUT 1
# define ZOOM_RATIO 1.2

void	zoom_action(t_fract *fract, int x, int y, int zoom_mode);
#endif
