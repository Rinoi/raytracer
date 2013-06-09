/*
** kdtree_sec.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  9 17:57:51 2013 karina martynava
** Last update Sun Jun  9 18:19:45 2013 karina martynava
*/

#include <values.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "rt.h"

t_inter		*check_obj_in_tree(t_l_obj *obj, t_st *droit)
{
  t_l_obj      	*ptn;
  t_inter	*inter;
  t_inter	*inter_m;

  ptn = obj;
  droit->neg = NULL;
  inter_m = NULL;
  while (ptn != NULL)
    {
      if ((inter = ptn->obj->cal_inter(ptn->obj, *droit)) != NULL)
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
  inter_update(inter_m, droit);
  return (inter_m);
}

float		v_abs(double nb)
{
  if (nb < 0)
    nb = -nb;
  return (nb);
}

int		my_check_for_p(t_kdtree *tree, t_st *droite, double t)
{
  t_ptn		p;

  p.x = droite->cord.x + (droite->vec.x * t);
  p.y = droite->cord.y + (droite->vec.y * t);
  p.z = droite->cord.z + (droite->vec.z * t);
  if ((tree->ori.x - 0.1 <= p.x && p.x <= tree->max.x + 0.1)
      && (tree->ori.y - 0.1 <= p.y && p.y <= tree->max.y + 0.1)
      && (tree->ori.z - 0.1 <= p.z && p.z <= tree->max.z) + 0.1)
    return (1);
  return (-1);
}
