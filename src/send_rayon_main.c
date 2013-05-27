/*
** send_rayon_main.c for Raytracing in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat May 11 02:21:22 2013 lucas mayol
** Last update Mon May 27 18:18:55 2013 lucas mayol
*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/rtv1.h"

static void    	my_cpy_tmp(t_ptn *tmp, t_ptn *ptn)
{
  ptn->x = tmp->x;
  ptn->y = tmp->y;
  ptn->z = tmp->z;
}

t_inter		*my_send_rayon_act(t_rs *rs, t_st *droit)
{
  t_ptn		*tmp;
  t_obj		*cp;
  t_inter	*my_return;
  int		i;

  i = 0;
  if ((my_return = malloc(sizeof(t_inter))) == NULL)
    exit(EXIT_FAILURE);
  cp = rs->obj;
  my_return->d = -1;
  while (cp != NULL && i != 2)
    {
      tmp = cp->cal_inter(cp, droit);
      if (tmp != NULL)
	{
	  if (my_return->d == -1 || my_call_dist(&droit->cord, tmp) <= my_return->d)
	    {
	      my_return->d = my_call_dist(&droit->cord, tmp);
	      my_return->obj = cp;
	      my_cpy_tmp(tmp, &my_return->ptn);
	    }
	  free(tmp);
	}
      cp = cp->next;
      if (cp == NULL)
	{
	  cp = rs->obj_inf;
	  i += 1;
	}
    }
  return (my_return->d != -1 ? my_return : NULL);
}

void		my_send_rayon(t_rs *rs, t_st *droit)
{
  t_inter	*inter;

  inter = my_send_rayon_act(rs, droit);
  if (inter == NULL)
    my_pixel_put_to_image(&rs->wind.img, droit->x, droit->y, 0x420);
  else
    {
      my_pixel_put_to_image(&rs->wind.img, droit->x, droit->y, my_cal_lux(rs, inter));
      free(inter);
    }
}

void	*send_rayon_main_a(void *rs)
{
  t_st	droit;

  droit.y = 0;
  droit.cord.x = ((t_rs *)(rs))->eyes.x;
  droit.cord.y = ((t_rs *)(rs))->eyes.y;
  droit.cord.z = ((t_rs *)(rs))->eyes.z;
  printf("%f, %f, %f\n", droit.cord.x, droit.cord.y, droit.cord.z);
  droit.vec.x = 500;
  while (droit.y <= 250)
    {
      droit.x = 0;
      while (droit.x <= 1000)
	{
	  droit.vec.y = 500 - droit.x;
	  droit.vec.z = 500 - droit.y;
	  my_send_rayon((t_rs *)rs, &droit);
	  droit.x += 1;
	}
      droit.y += 1;
      //      my_expose((t_rs *)rs);
    }
  return (NULL);
}

void	*send_rayon_main_b(void *rs)
{
  t_st	droit;

  droit.y = 251;
  droit.cord.x = ((t_rs *)(rs))->eyes.x;
  droit.cord.y = ((t_rs *)(rs))->eyes.y;
  droit.cord.z = ((t_rs *)(rs))->eyes.z;
  droit.vec.x = 500;
  while (droit.y <= 500)
    {
      droit.x = 0;
      while (droit.x <= 1000)
	{
	  droit.vec.y = 500 - droit.x;
	  droit.vec.z = 500 - droit.y;
	  my_send_rayon((t_rs *)rs, &droit);
	  droit.x += 1;
	}
      droit.y += 1;
      //my_expose((t_rs *)rs);
    }
  return (NULL);
}

void	*send_rayon_main_c(void *rs)
{
  t_st	droit;

  droit.y = 501;
  droit.cord.x = ((t_rs *)(rs))->eyes.x;
  droit.cord.y = ((t_rs *)(rs))->eyes.y;
  droit.cord.z = ((t_rs *)(rs))->eyes.z;
  droit.vec.x = 500;
  while (droit.y <= 750)
    {
      droit.x = 0;
      while (droit.x <= 1000)
	{
	  droit.vec.y = 500 - droit.x;
	  droit.vec.z = 500 - droit.y;
	  my_send_rayon((t_rs *)rs, &droit);
	  droit.x += 1;
	}
      droit.y += 1;
      //my_expose((t_rs *)rs);
    }
  return (NULL);
}

void	*send_rayon_main_d(void *rs)
{
  t_st	droit;

  droit.y = 751;
  droit.cord.x = ((t_rs *)(rs))->eyes.x;
  droit.cord.y = ((t_rs *)(rs))->eyes.y;
  droit.cord.z = ((t_rs *)(rs))->eyes.z;
  droit.vec.x = 500;
  while (droit.y <= 1000)
    {
      droit.x = 0;
      while (droit.x <= 1000)
	{
	  droit.vec.y = 500 - droit.x;
	  droit.vec.z = 500 - droit.y;
	  my_send_rayon((t_rs *)rs, &droit);
	  droit.x += 1;
	}
      droit.y += 1;
      //my_expose((t_rs *)rs);
    }
  return (NULL);
}

void		send_rayon_main(t_rs *rs)
{
  pthread_t	thread_1;
  pthread_t	thread_2;
  pthread_t	thread_3;
  pthread_t	thread_4;

  pthread_create(&thread_1, NULL, send_rayon_main_a, (void *)rs);
  pthread_create(&thread_2, NULL, send_rayon_main_b, (void *)rs);
  pthread_create(&thread_3, NULL, send_rayon_main_c, (void *)rs);
  pthread_create(&thread_4, NULL, send_rayon_main_d, (void *)rs);
}
