/*
** creat_matrice_rot.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Mon May 27 23:59:11 2013 lucas mayol
** Last update Tue May 28 00:09:03 2013 lucas mayol
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	"rt.h"

double		*matrice_rot_x(double angle)
{
  double	*matrice;
  
  if ((matrice = creat_matrice()) == NULL)
    return (NULL);
  matrice[5] = cos(RAD(angle));
  matrice[6] = - sin(RAD(angle));
  matrice[9] = sin(RAD(angle));
  matrice[10] = cos(RAD(angle));
  return (matrice);
}

double		*matrice_rot_y(double angle)
{
  double	*matrice;
  
  if ((matrice = creat_matrice()) == NULL)
    return (NULL);
  matrice[0] = cos(RAD(angle));
  matrice[2] = sin(RAD(angle));
  matrice[8] = - sin(RAD(angle));
  matrice[10] = cos(RAD(angle));
  return (matrice);
}

double		*matrice_rot_z(double angle)
{
  double	*matrice;
  
  if ((matrice = creat_matrice()) == NULL)
    return (NULL);
  matrice[0] = cos(RAD(angle));
  matrice[1] = - sin(RAD(angle));
  matrice[4] = sin(RAD(angle));
  matrice[5] = cos(RAD(angle));
  return (matrice);
}
