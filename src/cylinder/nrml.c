/*
** nrml.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 08:04:31 2013 karina martynava
** Last update Fri Jun  7 18:13:13 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

t_ptn	*cylinder_nrml_a(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;
 
  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  nrml->x = ptn->x - obj->ptn.x;
  nrml->y = ptn->y - obj->ptn.y;
  nrml->z = 0;
  return (nrml);
}

void	call_proj(float d, t_obj *obj, t_ptn *m)
{
  t_ptn	*mat;

  m->x = 0;
  m->y = 0;
  m->z = -1;
  mat = mul_m_p(obj->matrix_inv, m);
  m->x = mat->x * d + obj->ptn.x;
  m->y = mat->y * d + obj->ptn.y;
  m->z = mat->z * d + obj->ptn.z;
  free(mat);
}

t_ptn	*cylinder_nrml(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;
  //  t_ptn	*nrml2;
  t_ptn	proj;
  float	h;
  float	d;

  /* nrml2 = cylinder_nrml_a(obj, ptn); */
  /* printf("ORI : %f, %f, %f\n", nrml2->x, nrml2->y, nrml2->z); */
  /* free(nrml2); */
  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  h = sqrt(pow(obj->ptn.x - ptn->x, 2)
	   + pow(obj->ptn.y - ptn->y, 2)
	   + pow(obj->ptn.z - ptn->z, 2));
  d = pow(h, 2) - pow(*((float *)(obj->data)), 2);
  //  printf("d2 = %f\n", d);
  if (d < 0)
    d = -d;
  d = sqrt(d);
  //  printf("h : %f, op : %f, d : %f\n", h, *((float*)(obj->data)), d);
  call_proj(d, obj, &proj);
  nrml->x = ptn->x - proj.x;
  nrml->y = ptn->y - proj.y;
  nrml->z = ptn->z - proj.z;
  //  printf("ptn : %f %f %f\n", ptn->x, ptn->y, ptn->z);
  //  printf("proj %f %f %f\n", proj.x, proj.y, proj.z);
  //  printf("NEW : %f, %f, %f\n\n", nrml->x, nrml->y, nrml->z);
  //free(nrml);
  if (obj->mat->bump != 0)
    my_bump(nrml, ptn, obj->mat->bump);
  return (nrml);
}

t_ptn	*cylinder_nrml_inv(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;
 
  nrml = cylinder_nrml(obj, ptn);
  nrml->x = -nrml->x;
  nrml->y = -nrml->y;
  nrml->z = -nrml->z;
  return (nrml);
}
