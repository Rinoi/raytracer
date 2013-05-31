/*
** send_rayon_main.c for Raytracing in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat May 11 02:21:22 2013 lucas mayol
** Last update Fri May 31 18:08:58 2013 karina martynava
*/

#include <stdlib.h>
#include <stdio.h>
#include "rt.h"

int     get_img_color(t_img *img, int x, int y);
int	convert_col(float col[3]);
void	enligten(t_inter *point, t_rs *rs, float col[3], t_st *st);

t_inter		*my_send_rayon_act(t_rs *rs, t_st *droit)
{
  t_obj		*ptn;
  t_inter	*inter;
  t_inter	*inter_m;

  ptn = rs->obj;
  inter_m = NULL;
  while (ptn != NULL)
    {
      inter = ptn->cal_inter(ptn, *droit);
      if (inter != NULL)
	{
	  if (inter_m == NULL || inter_m->d > inter->d)
	    {
	      free(inter_m);
	      inter->obj = ptn;
	      inter_m = inter;
	    }
	  else
	    free(inter);
	}
      ptn = ptn->next;
    }
  if (inter_m != NULL)
    {
      inter_m->ptn.x = droit->cord.x + droit->vec.x * inter_m->d;
      inter_m->ptn.y = droit->cord.y + droit->vec.y * inter_m->d;
      inter_m->ptn.z = droit->cord.z + droit->vec.z * inter_m->d;
      /* printf("PI : %f %f %f\n\n", inter_m->ptn.x, inter_m->ptn.y, inter_m->ptn.z); */
    }
  return (inter_m);
}

void		my_send_rayon(t_rs *rs, t_st *droit)
{
  t_inter	*inter;
  int		color;
  float		col[4];
  int		x;
  int		y;

  //  printf("%f %f\n", droit->vec.y, droit->vec.x);
  col[0] = 0;
  col[1] = 0;
  col[2] = 0;
  col[3] = 1; /////////// REFLEXION
  x = droit->x;
  y = droit->y;
  color = get_img_color(&rs->bckground, x / 2, y / 2);
  inter = my_send_rayon_act(rs, droit);
  if (inter)
    {
      enligten(inter, rs, col, droit);
      color = convert_col(col);
      free(inter);
    }
  my_pixel_put_to_image(&rs->wind.img, droit->x, droit->y, color);
}

void		*send_rayon_main_act(void *dt)
{
  t_st		droit;
  t_data_t	*data;

  data = ((t_data_t *)(dt));
  droit.y = data->ini;
  printf("%f\n", data->rs->eyes->cam.x);
  droit.cord.x = data->rs->eyes->cam.x;
  droit.cord.y = data->rs->eyes->cam.y;
  droit.cord.z = data->rs->eyes->cam.z;
  printf("HERE %f, %f, %f\n", droit.cord.x, droit.cord.y, droit.cord.z);
  droit.vec.x = data->rs->eyes->larg / 2;
  while (droit.y <= data->max)
    {
      droit.x = 0;
      while (droit.x <= data->rs->wind.img.y)
	{
	  droit.vec.y = data->rs->eyes->larg / 2 - droit.x / 2.0f;
	  droit.vec.z = data->rs->eyes->larg / 2 - droit.y / 2.0f;
	  my_send_rayon(data->rs, &droit);
	  droit.x += 1;
	}
      droit.y += 1;
    }
  printf("END\n");
  data->rs->thr += 1;
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
  rs->thr = 0;
  creat_thread(rs, 0, 1 * (rs->wind.img.x / 4));
  creat_thread(rs, 1 * (rs->wind.img.x / 4), 2 * (rs->wind.img.x / 4));
  creat_thread(rs, 2 * (rs->wind.img.x / 4), 3 * (rs->wind.img.x / 4));
  creat_thread(rs, 3 * (rs->wind.img.x / 4), 4 * (rs->wind.img.x / 4));
}
