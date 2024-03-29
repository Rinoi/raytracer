/*
** opération.c for opération in /home/mayol_l//proj_perso/openGL
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Thu Apr 11 14:02:53 2013 lucas mayol
** Last update Thu Jun  6 23:09:38 2013 karina martynava
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	"rt.h"

double		*mul_matrice(double *m1, double *m2)
{
  double	*matrice;

  if ((matrice = malloc(sizeof(double) * 16)) == NULL)
    {
      printf("malloc error\n");
      exit(EXIT_FAILURE);
    }

  matrice[0] = m1[0] * m2[0] + m1[1] * m2[4] + m1[2] * m2[8] + m1[3] * m2[12];
  matrice[1] = m1[0] * m2[1] + m1[1] * m2[5] + m1[2] * m2[9] + m1[3] * m2[13];
  matrice[2] = m1[0] * m2[2] + m1[1] * m2[6] + m1[2] * m2[10] + m1[3] * m2[14];
  matrice[3] = m1[0] * m2[3] + m1[1] * m2[7] + m1[2] * m2[11] + m1[3] * m2[15];

  matrice[4] = m1[4] * m2[0] + m1[5] * m2[4] + m1[4] * m2[8] + m1[4] * m2[12];
  matrice[5] = m1[4] * m2[1] + m1[5] * m2[5] + m1[5] * m2[9] + m1[5] * m2[13];
  matrice[6] = m1[4] * m2[2] + m1[5] * m2[6] + m1[6] * m2[10] + m1[6] * m2[14];
  matrice[7] = m1[4] * m2[3] + m1[5] * m2[7] + m1[7] * m2[11] + m1[7] * m2[15];

  matrice[8] = m1[8] * m2[0] + m1[9] * m2[4] + m1[10] * m2[8] + m1[11] * m2[12];
  matrice[9] = m1[8] * m2[1] + m1[9] * m2[5] + m1[10] * m2[9] + m1[11] * m2[13];
  matrice[10] = m1[8] * m2[2] + m1[9] * m2[6] + m1[10] * m2[10] + m1[11] * m2[14];
  matrice[11] = m1[8] * m2[3] + m1[9] * m2[7] + m1[10] * m2[11] + m1[11] * m2[15];

  matrice[12] = m1[12] * m2[0] + m1[13] * m2[4] + m1[14] * m2[8] + m1[15] * m2[12];
  matrice[13] = m1[12] * m2[1] + m1[13] * m2[5] + m1[14] * m2[9] + m1[15] * m2[13];
  matrice[14] = m1[12] * m2[2] + m1[13] * m2[6] + m1[14] * m2[10] + m1[15] * m2[14];
  matrice[15] = m1[12] * m2[3] + m1[13] * m2[7] + m1[14] * m2[11] + m1[15] * m2[15];

  return (matrice);
}

t_ptn		*mul_m_p(double *matrice, t_ptn *ptn)
{
  t_ptn		*my_return;

  if (matrice == NULL)
    return (ptn);
  if (ptn == NULL)
    return (NULL);
  if ((my_return = malloc(sizeof(t_ptn))) == NULL)
    return (NULL);
  my_return->x = matrice[0] * ptn->x + matrice[1] * ptn->y + matrice[2] * ptn->z;
  my_return->y = matrice[4] * ptn->x + matrice[5] * ptn->y + matrice[6] * ptn->z;
  my_return->z = matrice[8] * ptn->x + matrice[9] * ptn->y + matrice[10] * ptn->z;
  return (my_return);
}
