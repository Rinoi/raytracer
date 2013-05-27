/*
** boxing.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Apr 17 17:44:42 2013 lucas mayol
** Last update Fri May 17 14:06:24 2013 lucas mayol
*/

#include <stdio.h>
#include "rtv1.h"

void	ini_ptn(t_ptn *ptn, float x, float y, float z)
{
  ptn->x = x;
  ptn->y = y;
  ptn->z = z;
}

void	my_multy_ptn(t_ptn *ptn, float x, float y, float z)
{
  multipli_x(ptn, x);
  multipli_y(ptn, y);
  multipli_z(ptn, z);
}

void	boxin_triangle(t_obj *obj)
{
  //  printf("boxin tri\n")
  obj->data[0] += obj->ptn.x;
  obj->data[1] += obj->ptn.y;
  obj->data[2] += obj->ptn.z;
  obj->data[3] += obj->ptn.x;
  obj->data[4] += obj->ptn.y;
  obj->data[5] += obj->ptn.z;
  /* printf("TRIANGLE : \n\tA1 : x %f, y %f, z %f\n", obj->ptn.x, obj->ptn.y, obj->ptn.z); */
  /* printf("\tA2 : x %f, y %f, z %f\n", obj->data[0], obj->data[1], obj->data[2]); */
  /* printf("\tA3 : x %f, y %f, z %f\n", obj->data[3], obj->data[4], obj->data[5]); */
  obj->box.origine.x = obj->ptn.x;
  obj->box.lenght.x = obj->ptn.x;
  obj->box.origine.y = obj->ptn.y;
  obj->box.lenght.y = obj->ptn.y;
  obj->box.origine.z = obj->ptn.z;
  obj->box.lenght.z = obj->ptn.z;

  obj->box.origine.x = obj->data[0] < obj->box.origine.x
    ? obj->data[0] : obj->box.origine.x;
  obj->box.origine.y = obj->data[1] < obj->box.origine.y
    ? obj->data[1] : obj->box.origine.y;
  obj->box.origine.z = obj->data[2] < obj->box.origine.z
    ? obj->data[2] : obj->box.origine.z;
  obj->box.lenght.x = obj->data[0] > obj->box.lenght.x
    ? obj->data[0] : obj->box.lenght.x;
  obj->box.lenght.y = obj->data[1] > obj->box.lenght.y
    ? obj->data[1] : obj->box.lenght.y;
  obj->box.lenght.z = obj->data[2] > obj->box.lenght.z
    ? obj->data[2] : obj->box.lenght.z;

  obj->box.origine.x = obj->data[3] < obj->box.origine.x
    ? obj->data[3] : obj->box.origine.x;
  obj->box.origine.y = obj->data[4] < obj->box.origine.y
    ? obj->data[4] : obj->box.origine.y;
  obj->box.origine.z = obj->data[5] < obj->box.origine.z
    ? obj->data[5] : obj->box.origine.z;
  obj->box.lenght.x = obj->data[3] > obj->box.lenght.x
    ? obj->data[3] : obj->box.lenght.x;
  obj->box.lenght.y = obj->data[4] > obj->box.lenght.y
    ? obj->data[4] : obj->box.lenght.y;
  obj->box.lenght.z = obj->data[5] > obj->box.lenght.z
    ? obj->data[5] : obj->box.lenght.z;

  /* printf("BOXING : \n"); */
  /* printf("\torigine : x %f, y %f, z %f\n", obj->box.origine.x, obj->box.origine.y, obj->box.origine.z); */
  /* printf("\tmax : x %f, y %f, z %f\n", obj->box.lenght.x, obj->box.lenght.y, obj->box.lenght.z); */
  obj->box.lenght.x = sqrt(pow(obj->box.origine.x - obj->box.lenght.x, 2));
  obj->box.lenght.y = sqrt(pow(obj->box.origine.y - obj->box.lenght.y, 2));
  obj->box.lenght.z = sqrt(pow(obj->box.origine.z - obj->box.lenght.z, 2));
  /* printf("\tlenght : x %f, y %f, z %f\n", obj->box.lenght.x, obj->box.lenght.y, obj->box.lenght.z); */
  obj->data[0] -= obj->ptn.x;
  obj->data[1] -= obj->ptn.y;
  obj->data[2] -= obj->ptn.z;
  obj->data[3] -= obj->ptn.x;
  obj->data[4] -= obj->ptn.y;
  obj->data[5] -= obj->ptn.z;
  //  printf("\n\n");
}

void	boxin_sphere(t_obj *obj)
{
  obj->box.origine.x = obj->ptn.x - obj->data[0];
  obj->box.origine.y = obj->ptn.y - obj->data[0];
  obj->box.origine.z = obj->ptn.z - obj->data[0];
  obj->box.lenght.x = obj->data[0] * 2;
  obj->box.lenght.y = obj->data[0] * 2;
  obj->box.lenght.z = obj->data[0] * 2;
}

void	boxin_cylindre(t_obj *obj)
{
  t_ptn	ptn;

  ini_ptn(&ptn, obj->ptn.x, obj->ptn.y, obj->ptn.z + obj->data[1]);
  my_multy_ptn(&ptn, obj->rot.x, obj->rot.y, obj->rot.z);
  obj->box.lenght.x = sqrt(pow(obj->ptn.x - (ptn.x + obj->data[0]), 2));
  obj->box.lenght.y = sqrt(pow(obj->ptn.y - (ptn.y + obj->data[0]), 2));
  obj->box.lenght.z = sqrt(pow(obj->ptn.z - (ptn.z + obj->data[0]), 2));
  obj->box.origine.x = ptn.x > obj->ptn.x ? obj->ptn.x : ptn.x;
  obj->box.origine.y = ptn.y > obj->ptn.y ? obj->ptn.y : ptn.y;
  obj->box.origine.x = ptn.x > obj->ptn.z ? obj->ptn.z : ptn.z;
}

void	boxin_cone(t_obj *obj)
{
  t_ptn	ptn;

  ini_ptn(&ptn, obj->ptn.x, obj->ptn.y, obj->ptn.z + obj->data[1]);
  my_multy_ptn(&ptn, obj->rot.x, obj->rot.y, obj->rot.z);
  obj->box.lenght.x = sqrt(pow((obj->ptn.x + obj->data[0]) - (ptn.x + obj->data[0]), 2));
  obj->box.lenght.y = sqrt(pow((obj->ptn.y + obj->data[0]) - (ptn.y + obj->data[0]), 2));
  obj->box.lenght.z = sqrt(pow((obj->ptn.z + obj->data[0]) - (ptn.z + obj->data[0]), 2));
  obj->box.origine.x = ptn.x > obj->ptn.x ? obj->ptn.x : ptn.x;
  obj->box.origine.y = ptn.y > obj->ptn.y ? obj->ptn.y : ptn.y;
  obj->box.origine.x = ptn.x > obj->ptn.z ? obj->ptn.z : ptn.z;
}
