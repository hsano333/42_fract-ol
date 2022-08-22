/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:54:57 by hsano             #+#    #+#             */
/*   Updated: 2022/08/22 18:50:17 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fract.h"
#include "ft_printf.h"
#include "image.h"

#define	IM1_SX		242
#define	IM1_SY		242
int	bpp1;
int	sl1;
int	endian1;
char	*data1;


int	color_map_2(unsigned char *data,int bpp,int sl,int w,int h,int endian, int type,t_fract	*fract)
{
  int	x;
  int	y;
  int	opp;
  int	dec;
  int	color;
  int	color2;
  unsigned char *ptr;
int	local_endian;

  int a = 0x11223344;
  if (((unsigned char *)&a)[0] == 0x11)
    local_endian = 1;
  else
    local_endian = 0;
  
  opp = bpp/8;
  printf("(opp : %d) ",opp);
  y = h;
  while (y--)
    {
      ptr = data+y*sl;
      x = w;
      while (x--)
        {
	  if (type==2)
	    color = (y*255)/w+((((w-x)*255)/w)<<16)
	      +(((y*255)/h)<<8);
	  else
	    color = (x*255)/w+((((w-x)*255)/w)<<16)+(((y*255)/h)<<8);
          color2 = mlx_get_color_value(fract->mlx,color);
	  dec = opp;
	  while (dec--)
	    if (endian==local_endian)
	      {
		if (endian)
		  *(ptr+x*opp+dec) = ((unsigned char *)(&color2))[4-opp+dec];
		else
		  *(ptr+x*opp+dec) = ((unsigned char *)(&color2))[dec];
	      }
	    else
	      {
		if (endian)
		  *(ptr+x*opp+dec) = ((unsigned char *)(&color2))[opp-1-dec];
		else
		  *(ptr+x*opp+dec) = ((unsigned char *)(&color2))[3-dec];
	      }
        }
    }
  return (1);
}


void	put_image(t_fract	*fract)
{

	void    *im1;
	if (!(im1 = mlx_new_image(fract->mlx,IM1_SX,IM1_SY)))
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	data1 = mlx_get_data_addr(im1,&bpp1,&sl1,&endian1);
	color_map_2((unsigned char*)data1,bpp1,sl1,IM1_SX,IM1_SY,endian1, 1,fract);
	mlx_put_image_to_window(fract->mlx,fract->window,im1,-20,-20);
	mlx_put_image_to_window(fract->mlx,fract->window,im1,80,80);
	mlx_destroy_image(fract->mlx, im1);
	//mlx_put_image_to_window(fract->mlx,fract->window,im1,180,180);

}

int main(int argc, char** argv)
{
	t_fract	fract;

	init(argc, argv, &fract);
	create_image(&fract);
	mlx_put_image_to_window(fract.mlx, fract.window, fract.image_info.image, 0, 0);
	mlx_loop(fract.mlx);
	return (0);
}
