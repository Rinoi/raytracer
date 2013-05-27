/*
** reflexion.c for rt in /home/martyn_k//svn/Raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sat May 11 16:40:23 2013 karina martynava
** Last update Mon May 13 21:15:50 2013 karina martynava
*/

#include <stdio.h>
#include <stdlib.h>
#include "rtv1.h"

t_inter		*my_send_rayon_act(t_rs *rs, t_st *droit);

#define MAX_DEPTH 1

void	new_straight(t_st *droit, t_inter *last)
{
  t_ptn	*nrml;
  float	scal;

  droit->power -= last->dist;
  droit->cord.x = droit->cord.x + last->dist * droit->vec.x;
  droit->cord.y = droit->cord.y + last->dist * droit->vec.y;
  droit->cord.z = droit->cord.z + last->dist * droit->vec.z;
  nrml = (last->obj->cal_norm)(last->obj, &(last->ptn));
  scal = droit->cord.x * nrml->x + droit->cord.y * nrml->y;
  scal += droit->cord.z * nrml->z;
  scal = 2 * scal;
  droit->vec.x = scal * droit->vec.x - nrml->x;
  droit->vec.y = scal * droit->vec.y - nrml->y;
  droit->vec.z = scal * droit->vec.z - nrml->z;
}

void	cpy_straight(t_st *droit, t_st *futur)
{
  futur->x = droit->x;
  futur->y = droit->y;
  futur->power = droit->power;
  futur->vec.x = droit->vec.x;
  futur->vec.y = droit->vec.y;
  futur->vec.z = droit->vec.z;
  futur->cord.x = droit->cord.x;
  futur->cord.y = droit->cord.y;
  futur->cord.z = droit->cord.z;
}

int	find_nxt_obj(t_rs *rs, t_st *droit, int *cmp_color, t_inter *last)
{
  t_inter	*inter;

  //  new_straight(droit, last);
  inter = my_send_rayon_act_kdtree(rs, droit);
  if (inter == NULL)
    return (0);
  *cmp_color = inter->obj->color;
  free(inter);
  return (1);
}

void		my_send_rayon(t_rs *rs, t_st *droit)
{
  t_inter	*inter;
  int		final_color;
  int		depth;
  int		ref_factor;
  int		cmp_color;
  t_st		futur;
  int		bol_nxt_obj;

  depth = 0;
  inter = my_send_rayon_act/* _kdtree */(rs, droit);
  if (inter == NULL)
    my_pixel_put_to_image(&rs->wind.img, droit->x, droit->y, 0x420);
  else
    {
      final_color = 0;
      ref_factor = 1;
      cpy_straight(droit, &futur);
      while (depth < MAX_DEPTH && ref_factor > 0 /* && bol_nxt_obj */)
      	{
	  printf("HELLO\n");
	  cmp_color = my_cal_lux(rs, inter);
      	  final_color += cmp_color * ref_factor;
	  	  new_straight(&futur, inter);
      	  /* bol_nxt_obj = find_nxt_obj(rs, &futur, &cmp_color, inter); */
      	  ref_factor = ref_factor * inter->obj->ref;
      	  depth++;
      	}
      my_pixel_put_to_image(&rs->wind.img, droit->x, droit->y, final_color/* my_cal_lux(rs, inter) */);
      free(inter);
    }
}

/* void		my_send_rayon(t_rs *rs, t_st *droit) */
/* { */
/*   t_inter	*inter; */
/*   int		final_color; */
/*   int		depth; */
/*   int		ref_factor; */
/*   int		bol_nxt_obj; */
/*   int		cmp_color; */
/*   t_st		futur; */

/*   depth = 0; */
/*   inter = my_send_rayon_act_kdtree(rs, droit); */
/*   if (inter == NULL) */
/*     my_pixel_put_to_image(&rs->wind.img, droit->x, droit->y, 0x00000000); */
/*   else */
/*     { */
/*       bol_nxt_obj = 1; */
/*       final_color = 0; */
/*       ref_factor = 1; */
/*       cmp_color = inter->obj->color; */
/*       /\* while (depth < MAX_DEPTH && ref_factor > 0 && bol_nxt_obj) *\/ */
/*       /\* 	{ *\/ */
/* 	  final_color += cmp_color * ref_factor; */
/* 	  /\* bol_nxt_obj = find_nxt_obj(rs, &futur, &cmp_color, inter); *\/ */
/*       	  /\* ref_factor = ref_factor * inter->obj->ref; *\/ */
/*       	  /\* depth++; *\/ */
/*       	/\* } *\/ */
/*       my_pixel_put_to_image(&rs->wind.img, droit->x, droit->y, final_color); */
/*       free(inter); */
/*     } */
/* } */
