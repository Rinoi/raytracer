/*
** boxing.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Apr 17 17:44:42 2013 lucas mayol
** Last update Sun Jun  9 00:53:34 2013 lucas mayol
*/

#include <stdio.h>
#include "rt.h"

void	boxin_triangle_s(t_tri *tri, t_obj *obj)
{
  obj->box.origine.x = tri->a2.x < obj->box.origine.x
    ? tri->a2.x : obj->box.origine.x;
  obj->box.origine.y = tri->a2.y < obj->box.origine.y
    ? tri->a2.y : obj->box.origine.y;
  obj->box.origine.z = tri->a2.z < obj->box.origine.z
    ? tri->a2.z : obj->box.origine.z;
  obj->box.lenght.x = tri->a2.x > obj->box.lenght.x
    ? tri->a2.x : obj->box.lenght.x;
  obj->box.lenght.y = tri->a2.y > obj->box.lenght.y
    ? tri->a2.y : obj->box.lenght.y;
  obj->box.lenght.z = tri->a2.z > obj->box.lenght.z
    ? tri->a2.z : obj->box.lenght.z;
}

void	boxin_triangle_ss(t_tri *tri, t_obj *obj)
{
  obj->box.origine.x = tri->a3.x < obj->box.origine.x
    ? tri->a3.x : obj->box.origine.x;
  obj->box.origine.y = tri->a3.y < obj->box.origine.y
    ? tri->a3.y : obj->box.origine.y;
  obj->box.origine.z = tri->a3.z < obj->box.origine.z
    ? tri->a3.z : obj->box.origine.z;
  obj->box.lenght.x = tri->a3.x > obj->box.lenght.x
    ? tri->a3.x : obj->box.lenght.x;
  obj->box.lenght.y = tri->a3.y > obj->box.lenght.y
    ? tri->a3.y : obj->box.lenght.y;
  obj->box.lenght.z = tri->a3.z > obj->box.lenght.z
    ? tri->a3.z : obj->box.lenght.z;
}

void	boxin_triangle_sss(t_tri *tri, t_obj *obj)
{
  obj->box.lenght.x = sqrt(pow(obj->box.origine.x - obj->box.lenght.x, 2));
  obj->box.lenght.y = sqrt(pow(obj->box.origine.y - obj->box.lenght.y, 2));
  obj->box.lenght.z = sqrt(pow(obj->box.origine.z - obj->box.lenght.z, 2));
  tri->a2.x -= obj->ptn.x;
  tri->a2.y -= obj->ptn.y;
  tri->a2.z -= obj->ptn.z;
  tri->a3.x -= obj->ptn.x;
  tri->a3.y -= obj->ptn.y;
  tri->a3.z -= obj->ptn.z;
}

void	boxin_triangle(t_obj *obj)
{
  t_tri	*tri;

  tri = (t_tri*)(obj->data);
  tri->a2.x += obj->ptn.x;
  tri->a2.y += obj->ptn.y;
  tri->a2.z += obj->ptn.z;
  tri->a3.x += obj->ptn.x;
  tri->a3.y += obj->ptn.y;
  tri->a3.z += obj->ptn.z;
  obj->box.origine.x = obj->ptn.x;
  obj->box.lenght.x = obj->ptn.x;
  obj->box.origine.y = obj->ptn.y;
  obj->box.lenght.y = obj->ptn.y;
  obj->box.origine.z = obj->ptn.z;
  obj->box.lenght.z = obj->ptn.z;
  boxin_triangle_s(tri, obj);
  boxin_triangle_ss(tri, obj);
  boxin_triangle_sss(tri, obj);
}
