/*
** creat_matrice.c for creat in /home/mayol_l//proj_perso/openGL
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Thu Apr 11 13:52:32 2013 lucas mayol
** Last update Tue May 28 06:16:02 2013 lucas mayol
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	"rt.h"

double		*creat_matrice()
{
  double	*matrice;

  if ((matrice = malloc(sizeof(double) * 16)) == NULL)
    {
      printf("malloc error\n");
      exit(EXIT_FAILURE);
    }

  matrice[0] = 1;
  matrice[1] = 0;
  matrice[2] = 0;
  matrice[3] = 0;

  matrice[4] = 0;
  matrice[5] = 1;
  matrice[6] = 0;
  matrice[7] = 0;

  matrice[8] = 0;
  matrice[9] = 0;
  matrice[10] = 1;
  matrice[11] = 0;
 
  matrice[12] = 0;
  matrice[13] = 0;
  matrice[14] = 0;
  matrice[15] = 1;

  return (matrice);
}

void		creat_matrice_for_obj(t_obj *obj)
{
  double	*matrice;

  if ((obj->matrix = matrice_translat(obj->ptn.x, obj->ptn.y, obj->ptn.z))
      == NULL)
    return ;
}
