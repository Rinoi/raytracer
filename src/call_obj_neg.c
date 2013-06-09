/*
** call_obj_neg.c for rt in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Fri Jun  7 22:34:59 2013 lucas mayol
** Last update Sun Jun  9 16:28:22 2013 lucas mayol
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

static void	my_add_vec(t_ptn *ptn, t_ptn *plus, float r, int b)	
{
  if (b > 0)
    {
      ptn->x += plus->x * r;
      ptn->y += plus->y * r;
      ptn->z += plus->z * r;
    }
  else
    {
      ptn->x -= plus->x * r;
      ptn->y -= plus->y * r;
      ptn->z -= plus->z * r;
    }
}

void		call_obj_neg(t_st *droit, t_rs *rs)
{
  t_obj		*obj;
  t_inter	*inter;
  t_neg		neg;

  droit->neg = NULL;
  obj = rs->obj_neg;
  while (obj != NULL)
    {
      inter = obj->cal_inter(obj, *droit);
      if (inter != NULL)
	{
	  neg.deb = inter->d;
	  my_add_vec(&droit->cord, &droit->vec, inter->d + EPSILLON, 1);
	  free(inter);
	  if ((inter = obj->cal_inter(obj, *droit)) != NULL)
	    neg.end = inter->d;
	  else
	    neg.end = neg.deb + EPSILLON;
	  my_add_vec(&droit->cord, &droit->vec, neg.deb + EPSILLON, 1);
	  neg.obj = obj;
	  my_add_end_in_neg(&droit->neg, &neg);
	}
      free(inter);
      obj = obj->next;
    }
}
