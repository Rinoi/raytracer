/*
** creat_matrice.c for creat in /home/mayol_l//proj_perso/openGL
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Thu Apr 11 13:52:32 2013 lucas mayol
** Last update Tue May 28 07:20:34 2013 karina martynava
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
  double	*matrice2;

  if ((obj->matrix = matrice_rot_x(obj->rot.x)) == NULL)
    return ;

  matrice = matrice_rot_y(obj->rot.y);
  matrice2 = mul_matrice(matrice, obj->matrix);
  free(obj->matrix);
  obj->matrix = matrice2;
  free(matrice);
  matrice = matrice_rot_z(obj->rot.z);
  matrice2 = mul_matrice(matrice, obj->matrix);
  free(obj->matrix);
  obj->matrix = matrice2;
  free(matrice);
}
    
