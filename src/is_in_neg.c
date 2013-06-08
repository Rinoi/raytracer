/*
** in_in_neg.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Fri Jun  7 21:56:19 2013 lucas mayol
** Last update Sat Jun  8 12:25:19 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

int	is_in_neg(t_neg *obj, float d)
{
  t_neg	*ptn;

  ptn = obj;
  while (ptn != NULL)
    {
      if (ptn->deb - EPSILLON <= d && d <= ptn->end + EPSILLON)
	{
	  return (1);
	}
      ptn = ptn->next;
    }
  return (0);
}
