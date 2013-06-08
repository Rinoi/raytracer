/*
** my_bump.c for rt in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Fri Jun  7 02:13:31 2013 lucas mayol
** Last update Sat Jun  8 18:33:28 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

void	normalisation_vec(t_ptn *nrml)
{
  float	tmp;

  tmp = nrml->x * nrml->x + nrml->y * nrml->y + nrml->z * nrml->z;
  tmp = 1 / sqrtf(tmp);
  nrml->x *= tmp;
  nrml->y *= tmp;
  nrml->z *= tmp;
}

void    my_bump(t_ptn *nrml, t_ptn *ptn, float bump)
{
  float nx;
  float ny;
  float nz;
  t_ptn m_ptn;
  float tmp;

  initBruit3D(10, 10, 10, 2, 16);
  normalisation_vec(nrml);
  m_ptn.x = (ptn->x + 99999) * 0.1;
  m_ptn.y = (ptn->y + 99999) * 0.1;
  m_ptn.z = (ptn->z + 99999) * 0.1;
  nx = bruit_coherent3D(&m_ptn, 0.5);
  m_ptn.x = (ptn->y + 99999) * 0.1;
  m_ptn.y = (ptn->z + 99999) * 0.1;
  m_ptn.z = (ptn->x + 99999) * 0.1;
  ny = bruit_coherent3D(&m_ptn, 0.5);
  m_ptn.x = (ptn->z + 99999) * 0.1;
  m_ptn.y = (ptn->x + 99999) * 0.1;
  m_ptn.z = (ptn->y + 99999) * 0.1;
  nz = bruit_coherent3D(&m_ptn, 0.5);
  nrml->x = (1.0 - bump) * nrml->x + bump * nx;
  nrml->y = (1.0 - bump) * nrml->y + bump * ny;
  nrml->z = (1.0 - bump) * nrml->z + bump * nz;
  normalisation_vec(nrml);
}
