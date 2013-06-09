/*
** cord.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  9 18:08:51 2013 karina martynava
** Last update Sun Jun  9 18:09:11 2013 karina martynava
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "rt.h"
#include "obj_pars.h"

void	init_ptn_safety(t_ptn *ptn, t_ptn *obj)
{
  ptn->x = 0 + obj->x;
  ptn->y = 0 + obj->y;
  ptn->z = 0 + obj->z;
}

void	get_cord_face(t_vr **vr, char *str, t_ptn *ptn, t_ptn *obj)
{
  int	nb;

  nb = atoi(str);
  if (nb <= 0 || (*vr) == NULL)
    return ;
  init_ptn_safety(ptn, obj);
  while (nb <= (*vr)->total || nb - 1 >= (*vr)->total + 99)
    {
      if (nb - 1 <= (*vr)->total)
	{
	  if ((*vr)->prv == NULL)
	    return ;
	  *vr = (*vr)->prv;
	}
      else
	{
	  if ((*vr)->nxt == NULL)
            return ;
	  *vr = (*vr)->nxt;
	}
    }
  ptn->x = (*vr)->ptn[(nb - 1 - (*vr)->total)][0];
  ptn->y = (*vr)->ptn[(nb - 1 - (*vr)->total)][1];
  ptn->z = (*vr)->ptn[(nb - 1 - (*vr)->total)][2];
}
