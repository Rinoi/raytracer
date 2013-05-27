/*
** matrice_dumb.c for opengl in /home/mayol_l//proj_perso/openGL/matrice
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Mon Apr 29 16:59:11 2013 lucas mayol
** Last update Mon May 27 23:54:50 2013 lucas mayol
*/

#include <stdio.h>
#include <stdlib.h>

double		*matrice_dumb(double *matrice)
{
  double	*new_matrice;

  if ((new_matrice = malloc(sizeof(double) * 16)) == NULL)
    {
      printf("malloc error\n");
      exit(EXIT_FAILURE);
    }

  new_matrice[0] = matrice[0];
  new_matrice[1] = matrice[1];
  new_matrice[2] = matrice[2];
  new_matrice[3] = matrice[3];
  new_matrice[4] = matrice[4];
  new_matrice[5] = matrice[5];
  new_matrice[6] = matrice[6];
  new_matrice[7] = matrice[7];
  new_matrice[8] = matrice[8];
  new_matrice[9] = matrice[9];
  new_matrice[10] = matrice[10];
  new_matrice[11] = matrice[11];
  new_matrice[12] = matrice[12];
  new_matrice[13] = matrice[13];
  new_matrice[14] = matrice[14];
  new_matrice[15] = matrice[15];

  return (new_matrice);
}
