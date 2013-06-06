/*
** send_rayon_main.c for Raytracing in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat May 11 02:21:22 2013 lucas mayol
** Last update Thu Jun  6 18:13:51 2013 lucas mayol
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "rt.h"

#define	NB_PAT	3

t_patterns	g_pat[] =
  {
    {0, nrml_pattern},
    {1, vert_pattern},
    {2, alea_pattern}
  };

void		find_ori_ptn(t_inter *inter)
{
  t_ptn		*mat;

  inter->ori_ptn.x = inter->ptn.x - inter->obj->ptn.x;
  inter->ori_ptn.y = inter->ptn.y - inter->obj->ptn.y;
  inter->ori_ptn.z = inter->ptn.z - inter->obj->ptn.z;
  mat = mul_m_p(inter->obj->matrix, &inter->ori_ptn);
  inter->ori_ptn.x = mat->x + inter->obj->ptn.x;
  inter->ori_ptn.y = mat->y + inter->obj->ptn.y;
  inter->ori_ptn.z = mat->z + inter->obj->ptn.z;
  //  free(mat);
}

t_inter		*my_send_rayon_act(t_rs *rs, t_st *droit)
{
  t_obj		*ptn;
  t_inter	*inter;
  t_inter	*inter_m;

  ptn = rs->obj;
  inter_m = NULL;
  while (ptn != NULL)
    {
      if ((inter = ptn->cal_inter(ptn, *droit)) != NULL)
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
  if (inter_m == NULL)
    return (NULL);
  inter_m->ptn.x = droit->cord.x + droit->vec.x * inter_m->d;
  inter_m->ptn.y = droit->cord.y + droit->vec.y * inter_m->d;
  inter_m->ptn.z = droit->cord.z + droit->vec.z * inter_m->d;
  inter_m->rela_ptn = inter_m->ptn;
  find_ori_ptn(inter_m);
  return (inter_m);
}

void		*send_rayon_main_act(void *dt)
{
  t_st		droit;
  t_data_t	*data;
  int		i;

  i = 0;
  data = ((t_data_t *)(dt));
  droit.y = data->ini;
  droit.cord.x = data->rs->eyes->cam.x;
  droit.cord.y = data->rs->eyes->cam.y;
  droit.cord.z = data->rs->eyes->cam.z;
  droit.vec.x = data->rs->eyes->larg / 2;
  while (i < NB_PAT && i != -1)
    {
      if (g_pat[i].num == data->rs->env.pattern)
	{
	  (g_pat[i].ptr)(data, &droit);
	  i = -2;
	}
      i++;
    }
  if (i == -1)
    nrml_pattern(data, &droit);
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
  printf("TROLL %f %f %f\n", data->rs->eyes->cam.x, data->rs->eyes->cam.y, data->rs->eyes->cam.z);
  pthread_create(&thread, NULL, send_rayon_main_act, (void *)data);
}

void		send_rayon_main(t_rs *rs)
{
  rs->thr = 0;
  creat_thread(rs, 0, 1 * (rs->eyes->larg));
  /* creat_thread(rs, 1 * (rs->eyes->larg / 4), 2 * (rs->eyes->larg / 4)); */
  /* creat_thread(rs, 2 * (rs->eyes->larg / 4), 3 * (rs->eyes->larg / 4)); */
  /* creat_thread(rs, 3 * (rs->eyes->larg / 4), 4 * (rs->eyes->larg / 4)); */
  while (rs->thr != 1)
    usleep(100000);
}
