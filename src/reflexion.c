/*
** reflexion.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sat Jun  1 01:31:53 2013 karina martynava
** Last update Sat Jun  8 19:47:15 2013 karina martynava
*/

#include <unistd.h>
#include <stdlib.h>
#include "rt.h"

void	new_straight(t_st *droit, t_inter *last)
{
  t_ptn	*nrml;
  float	scal;

  droit->cord.x = last->ptn.x;
  droit->cord.y = last->ptn.y;
  droit->cord.z = last->ptn.z;
  nrml = (*(last->cal_norm))(last->obj, &(last->ptn));
  mult_vect(nrml, 1.0f / sqrt(scal_prod(nrml, nrml)));
  mult_vect(&droit->vec, 1.0f / sqrt(scal_prod(&droit->vec, &droit->vec)));
  scal = scal_prod(nrml, &droit->vec);
  scal = 2.0f * scal;
  droit->vec.x = droit->vec.x - scal * nrml->x;
  droit->vec.y = droit->vec.y - scal * nrml->y;
  droit->vec.z = droit->vec.z - scal * nrml->z;
  free(nrml);
}

void	col_update_reflex(float col[4], float tmp_col[4], t_inter *inter, t_st *st)
{
  col[0] = tmp_col[0] * col[3] + (1.0 - col[3]) * col[0];
  col[1] = tmp_col[1] * col[3] + (1.0 - col[3]) * col[1];
  col[2] = tmp_col[2] * col[3] + (1.0 - col[3]) * col[2];
  col[3] = (inter->obj->mat) ? col[3] * inter->obj->mat->reflex : 0;
  refraction(inter, st);
}

void	refl_init(t_st *refl, t_st *droit, int *cmb, int *bol)
{
  *refl = *droit;
  refl->ind_list = NULL;
  refl->indice = DEFAULT_INDICE;
  *cmb = 0;
  *bol = 0;
}

int	reflexion_time(t_rs *rs, t_st *droit, float col[4])
{
  t_inter	*inter;
  int		bol;
  int		cmb;
  float		tmp_col[4];
  t_st		refl;
  int		i;

  refl_init(&refl, droit, &cmb, &bol);
  while (cmb < MAXDEPTH && cmb != -1 && col[3] > 0.0f && (i = 0) == 0)
    {
      while (i < 3 && (tmp_col[i++] = 0) == 0);
      tmp_col[3] = col[3];
      inter = my_send_rayon_act(rs, &refl);
      bol = 1;
      if (inter != NULL && (bol = 1) && ++cmb)
	{
	  enligten(inter, rs, tmp_col, &refl);
	  col_update_reflex(col, tmp_col, inter, &refl);
	}
      else
	cmb = -1;
      free(inter);
    }
  return (bol);
}

void		my_send_rayon(t_rs *rs, t_st *droit, float col[4])
{
  col[0] = 0;
  col[1] = 0;
  col[2] = 0;
  col[3] = 1;
  reflexion_time(rs, droit, col);
}
