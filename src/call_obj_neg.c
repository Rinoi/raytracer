/*
** call_obj_neg.c for rt in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Fri Jun  7 22:34:59 2013 lucas mayol
** Last update Fri Jun  7 22:56:39 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

void		my_add_end_in_neg(t_neg **list, t_neg *elem)
{
  t_neg		*elemn;

  if ((elemn = malloc(sizeof(t_neg))) == NULL)
    exit(EXIT_FAILURE);
  elemn->deb = elem->deb;
  elemn->end = elem->deb + elem->end;
  elemn->obj = elem->obj;
  elemn->next = *list;
  *list = elemn;
}

void		call_obj_neg(t_st *droit, t_rs *rs)
{
  t_obj		*obj;
  t_inter	*inter;
  t_neg		neg;
  t_neg		*ptn;

  droit->neg = NULL;
  obj = rs->obj_neg;
  while (obj != NULL)
    {
      inter = obj->cal_inter(obj, *droit);
      if (inter != NULL)
	{
	  neg.deb = inter->d;
	  droit->cord.x += droit->vec.x * (inter->d + EPSILLON);
	  droit->cord.y += droit->vec.y * (inter->d + EPSILLON);
	  droit->cord.z += droit->vec.z * (inter->d + EPSILLON);
	  free(inter);
	  if ((inter = obj->cal_inter(obj, *droit)) != NULL)
	    neg.end = inter->d;
	  else
	    neg.end = neg.deb + EPSILLON;	    
	  droit->cord.x -= droit->vec.x * (neg.deb + EPSILLON);
	  droit->cord.y -= droit->vec.y * (neg.deb + EPSILLON);
	  droit->cord.z -= droit->vec.z * (neg.deb + EPSILLON);
	  neg.obj = obj;
	  my_add_end_in_neg(&droit->neg, &neg);
	}
      free(inter);
      obj = obj->next;
    }
  ptn = droit->neg;
  while (ptn != NULL)
    ptn = ptn->next;
}
