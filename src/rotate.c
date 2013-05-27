/*
** rotate.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Apr 17 18:12:30 2013 lucas mayol
** Last update Sun May 19 12:05:30 2013 lucas mayol
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/rtv1.h"

void	multipli_x(t_ptn *ptn, float angle)
{
  t_ptn	new;

  new.x = ptn->x;
  new.y = ptn->y * cos(RAD(angle)) + ptn->z * (- sin(RAD(angle)));
  new.z = ptn->y * sin(RAD(angle)) + ptn->z * cos(RAD(angle));
  ptn->x = new.x;
  ptn->y = new.y;
  ptn->z = new.z;
}

void	multipli_y(t_ptn *ptn, float angle)
{
  t_ptn	new;

  new.x = ptn->x * cos(RAD(angle)) + ptn->z * (sin(RAD(angle)));
  new.y = ptn->y;
  new.z = ptn->x * (- sin(RAD(angle))) + ptn->z * cos(RAD(angle));
  ptn->x = new.x;
  ptn->y = new.y;
  ptn->z = new.z;
}

void	multipli_z(t_ptn *ptn, float angle)
{
  t_ptn	new;

  new.x = ptn->x * cos(RAD(angle)) + ptn->y * (- sin(RAD(angle)));
  new.y = ptn->x * sin(RAD(angle)) + ptn->y * cos(RAD(angle));
  new.z = ptn->z;
  ptn->x = new.x;
  ptn->y = new.y;
  ptn->z = new.z;
}

double	*matrice_rot(double a, double x, double y, double z)
{
  double	*matrice;

  if ((matrice = malloc(sizeof(double) * 9)) == NULL)
    return (NULL);
  matrice[0] = x * x + (1 - (x * x)) * cos(RAD(a));
  matrice[1] = x * y * (1 - cos(RAD(a))) - z * sin(RAD(a));
  matrice[2] = x * z * (1 - cos(RAD(a))) + y * sin(RAD(a));

  matrice[3] = y * x * (1 - cos(RAD(a))) + z * sin(RAD(a));
  matrice[4] = y * y + (1 - (y * y)) * cos(RAD(a));
  matrice[5] = y * z * (1 - cos(RAD(a))) - x * sin(RAD(a));

  matrice[6] = z * x * (1 - cos(RAD(a))) - y * sin(RAD(a));
  matrice[7] = z * y * (1 - cos(RAD(a))) + x * sin(RAD(a));
  matrice[8] = z * z + (1 - (z * z)) * cos(RAD(a));
  return (matrice);
}

t_ptn	*mul_matrice(double *matrice, t_ptn *ptn)
{
  t_ptn	*my_return;

  if ((my_return = malloc(sizeof(t_ptn))) == NULL)
    return (NULL);
  my_return->x = ptn->x * matrice[0] + ptn->x * matrice[1] + ptn->x * matrice[2];
  my_return->y = ptn->y * matrice[3] + ptn->y * matrice[4] + ptn->y * matrice[5];
  my_return->z = ptn->z * matrice[6] + ptn->z * matrice[7] + ptn->z * matrice[8];
  return (my_return);
}
