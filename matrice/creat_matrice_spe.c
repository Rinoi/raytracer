/*
** creat_matrice_spe.c for opengl in /home/mayol_l//proj_perso/openGL/matrice
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Mon Apr 29 16:38:51 2013 lucas mayol
** Last update Mon May 27 23:56:23 2013 lucas mayol
*/

#include <stdio.h>
#include <stdlib.h>
#include "rt.h"

double		*matrice_translat(double x, double y, double z)
{
  double	*matrice;

  matrice = creat_matrice();

  matrice[3] = x;
  matrice[7] = y;
  matrice[11] = z;
  
  return (matrice);
}

double		*matrice_homo(double x, double y, double z)
{
  double	*matrice;

  matrice = creat_matrice();

  matrice[0] = x;
  matrice[5] = y;
  matrice[10] = z;

  return (matrice);
}
