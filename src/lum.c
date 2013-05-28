/*
** lum.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 04:06:32 2013 karina martynava
** Last update Tue May 28 04:10:14 2013 karina martynava
*/

float	lambert(t_ptn *lightray, t_ptn *nrml, float *coef_ref)
{
  float	lamb;

  lamb = scal_prod(lightray, nrml) * coef_ref;
  return (lamb);
}