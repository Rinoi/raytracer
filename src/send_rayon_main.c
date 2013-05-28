/*
** send_rayon_main.c for Raytracing in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat May 11 02:21:22 2013 lucas mayol
** Last update Tue May 28 04:45:01 2013 karina martynava
*/

#include <stdlib.h>
#include <stdio.h>
#include "rt.h"

t_inter		*my_send_rayon_act(t_rs *rs, t_st *droit)
{
  t_obj		*ptn;
  t_inter	*inter;
  t_inter	*inter_m;

  if (rs == NULL)
    printf("LOOOOOOOL\n");
  ptn = rs->obj;
  inter_m = NULL;
  while (ptn != NULL)
    {
      inter = ptn->cal_inter(ptn, droit);
      if (inter != NULL)
	{
	  if (inter_m == NULL || inter_m->d > inter->d)
	    {
	      free(inter_m);
	      inter_m = inter;
	    }
	  else
	    free(inter);
	}
      ptn = ptn->next;
    }
  return (inter_m);
}

void		my_send_rayon(t_rs *rs, t_st *droit)
{
  t_inter	*inter;

  inter = my_send_rayon_act(rs, droit);
  if (inter == NULL)
    my_pixel_put_to_image(&rs->wind.img, droit->x, droit->y, 0x420);
  else
    {
      my_pixel_put_to_image(&rs->wind.img, droit->x, droit->y, 0xFFFFFF);
      free(inter);
    }
}

void	*send_rayon_main_act(void *data)
{
  t_st	droit;

  droit.y = ((t_data_t *)(data))->ini;
  printf("%f\n", ((t_data_t *)(data))->rs->eyes->cam.x);
  droit.cord.x = ((t_data_t *)(data))->rs->eyes->cam.x;
  droit.cord.y = ((t_data_t *)(data))->rs->eyes->cam.y;
  droit.cord.z = ((t_data_t *)(data))->rs->eyes->cam.z;
  printf("HERE %f, %f, %f\n", droit.cord.x, droit.cord.y, droit.cord.z);
  droit.vec.x = ((t_data_t *)(data))->rs->eyes->larg / 2;
  while (droit.y <= ((t_data_t *)(data))->max)
    {
      droit.x = 0;
      while (droit.x <= ((t_data_t *)(data))->rs->eyes->larg)
	{
	  droit.vec.y = ((t_data_t *)(data))->rs->eyes->larg / 2 - droit.x;
	  droit.vec.z = ((t_data_t *)(data))->rs->eyes->larg / 2 - droit.y;
	  my_send_rayon(((t_data_t *)(data))->rs, &droit);
	  droit.x += 1;
	}
      droit.y += 1;
    }
  return (NULL);
}

void		creat_thread(t_rs *rs, int ini, int max)
{
  t_data_t	*data;
  pthread_t	thread;

  if ((data = malloc(sizeof(*data))) == NULL)
    return ;
  data->ini = ini;
  data->max = max;
  data->rs = rs;
  //  printf("%f\n", data->rs->eyes->cam.x);
  printf("TROLL %f %f %f\n", data->rs->eyes->cam.x, data->rs->eyes->cam.y, data->rs->eyes->cam.z);
  pthread_create(&thread, NULL, send_rayon_main_act, (void *)data);
}

void		send_rayon_main(t_rs *rs)
{
  creat_thread(rs, 0, 1 * (rs->eyes->larg / 4));
  creat_thread(rs, 1 * (rs->eyes->larg / 4), 2 * (rs->eyes->larg / 4));
  creat_thread(rs, 2 * (rs->eyes->larg / 4), 3 * (rs->eyes->larg / 4));
  creat_thread(rs, 3 * (rs->eyes->larg / 4), 4 * (rs->eyes->larg / 4));
}
