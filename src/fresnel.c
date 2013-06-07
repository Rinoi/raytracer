/*
** fresnel.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Thu Jun  6 23:23:12 2013 karina martynava
** Last update Sat Jun  8 00:37:48 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

float	lambert_coef(t_ptn *lightray, t_ptn *nrml, char attribute);
void	new_straight(t_st *droit, t_inter *last);

/* void	add_fresnel(t_st *st, t_inter *inter) */
/* { */
/*   t_fresnel	*new; */

/*   new = malloc(sizeof(*new)); */
/*   if (new == NULL) */
/*     return ; */
/*   new->obj = inter->obj; */
/*   new->in = inter->ptn; */
/*   new->next = NULL; */
/*   new->prev = st->ind_list; */
/*   new->dens = inter->obj->mat->indice; */
/*   if (st->ind_list == NULL) */
/*     { */
/*       st->ind_list = new; */
/*       return ; */
/*     } */
/*   while (st->ind_list != NULL && st->ind_list->next != NULL) */
/*     st->ind_list = st->ind_list->next; */
/*   st->ind_list->next = new; */
/* } */

/* void 	rm_fresnel(t_fresnel *sv) */
/* { */
/*   if (sv->next == NULL) */
/*     { */
/*       if (sv->prev != NULL) */
/* 	{ */
/* 	  sv->prev->next = NULL; */
/* 	  free(sv); */
/* 	} */
/*       return ; */
/*     } */
/*   sv->next->prev = sv->prev; */
/*   if (sv->prev != NULL) */
/*     sv->prev->next = sv->next; */
/* } */

/* void		fresnel_indice_list(t_inter *inter, t_st *st) */
/* { */
/*   t_fresnel	*sv; */

/*   sv = st->ind_list; */
/*   if (sv == NULL) */
/*     add_fresnel(st, inter); */
/*   else */
/*     { */
/*       while (sv != NULL && sv->prev != NULL) */
/* 	{ */
/* 	  if (sv->obj == inter->obj) */
/* 	    { */
/* 	      rm_fresnel(sv); */
/* 	      return ; */
/* 	    } */
/* 	} */
/*       add_fresnel(st, inter); */
/*     } */
/* } */

float	vec_prod_norm(t_ptn *u, t_ptn *v)
{
  t_ptn	w;

  w.x = u->y * v->z - u->z * v->y;
  w.y = u->z * v->x - u->x * v->z;
  w.z = u->x * v->y - u->y * v->x;
  return (sqrtf(scal_prod(&w, &w)));
}

void	refraction(t_inter *inter, t_st *st)
{
  if (inter->obj->mat == NULL || inter->obj->mat->indice == 0.0f)
    {
      new_straight(st, inter);
      return ;
    }
  st->cord.x = inter->ptn.x;
  st->cord.y = inter->ptn.y;
  st->cord.z = inter->ptn.z;
}
