/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:54:57 by hsano             #+#    #+#             */
/*   Updated: 2022/08/21 15:43:11 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"


void *mlx;
void *win1;
void *win2;

#include "fract.h"
#include "ft_printf.h"
//#include "include/ft_printf.h"
//
//
int gere_mouse(int x,int y,int button,void*toto)
{
  ft_printf("Mouse event -x=%d,y=%d,button=%d,,%ptoto new win\n",x,y,button,toto);
  mlx_destroy_window(mlx,win1);
  win1 = mlx_new_window(mlx,random()%500,random()%500,"new win");
  mlx_mouse_hook(win1,gere_mouse,0);
  return (0);
}


int main_test(void)
{
  //srandom(time(0));
  srandom(3);
  mlx = mlx_init();
  win1 = mlx_new_window(mlx,300,300,"win1");
  win2 = mlx_new_window(mlx,600,600,"win2");
  mlx_mouse_hook(win1,gere_mouse,0);
  mlx_mouse_hook(win2,gere_mouse,0);
  mlx_loop(mlx);
  return (0);
}

int main(int argc, char** argv)
//int main(void)
{
	//t_fract	fract_test;
	t_fract	fract;

	//fract = &fract_test;
	//main_test();
	ft_printf("start No.1\n");
	init(argc, argv, &fract);
	//
	//
	//
	//mlx_loop_hook(fract->mlx, detect_move, 0);
	mlx_loop(fract.mlx);
	ft_printf("int main end\n");
	return (0);
}
