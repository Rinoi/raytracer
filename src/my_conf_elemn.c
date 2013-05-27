/*
** my_conf_elemn.c for conf_elem in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sun Mar 17 11:12:10 2013 lucas mayol
** Last update Sun May 19 00:40:05 2013 lucas mayol
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/rtv1.h"
#include "../pars/pars.h"

int		my_conf_sphere(t_obj *elem)
{
  elem->data = malloc(sizeof(float) * 1);
  /* elem->id = 1; */
  elem->cal_inter = my_call_point_shere;
  elem->cal_lux_cos = my_cal_lux_cos_shere;
  /* elem->cal_text = my_call_texture_shere; */
  return (1);
}

int		my_conf_conus(t_obj *elem)
{
  elem->data = malloc(sizeof(float) * 2);
  elem->data[0] = 0;
  /* elem->id = 2; */
  elem->cal_inter = my_call_point_conus;
  elem->cal_lux_cos = my_cal_lux_cos_conus;
  elem->cal_norm = cal_norm_conus;
  /* elem->cal_lum = my_cal_lum_cone; */
  /* elem->cal_text = my_call_texture_shere; */
  return (2);
}

int		my_conf_cylinder(t_obj *elem)
{
  elem->data = malloc(sizeof(float) * 2);
  elem->data[0] = 0;
  /* elem->id = 3; */
  elem->cal_inter = my_call_point_cylinder;
  elem->cal_lux_cos = my_cal_lux_cos_cylinder;
  elem->cal_norm = cal_norm_cylinder;
  /* elem->cal_inter = my_call_point_cylindre; */
  /* elem->cal_lum = my_cal_lum_cylindre; */
  /* elem->cal_text = my_call_texture_cylindre; */
  return (3);
}

int		my_conf_plane(t_obj *elem)
{
  elem->data = malloc(sizeof(float) * 1);
  /* elem->id = 4; */
  /* elem->cal_inter = my_call_point_plan; */
  /* elem->cal_lum = my_cal_lum_plan; */
  /* elem->cal_text = my_call_texture_plan; */
  return (4);
}

int		my_conf_triangle(t_obj *elem)
{
  elem->data = malloc(sizeof(float) * 6);
  /* elem->id = 4; */
  elem->cal_inter = my_call_point_triangle;
  elem->cal_lux_cos = my_cal_lux_cos_triangle;
  elem->cal_norm = cal_norm_triangle;
  /* elem->cal_text = my_call_texture_plan; */
  return (5);
}

const t_fct_elem g_fct_tab[] =
  {
    {my_conf_sphere, SPHERE},
    {my_conf_conus, CONUS},
    {my_conf_plane, PLANE},
    {my_conf_cylinder, CYLINDER},
    {my_conf_triangle, TRIANGLE}
  };

int			my_conf_elem(t_obj *elem, t_noeud *n)
{
  int			i;

  elem->ptn.x = 0;
  elem->ptn.y = 0;
  elem->ptn.z = 0;
  elem->rot.x = 0;
  elem->rot.y = 0;
  elem->rot.z = 0;
  elem->color = 0xFFFFFFFF;
  i = 0;
  while (i < NB_DIFF_OBJ)
    if (my_strcmp(n->bal.name, g_fct_tab[i++].str) == 1)
      return (g_fct_tab[--i].ptr(elem));
  my_putstr("unknow tupe : ", 2);
  my_putstr(n->bal.name, 2);
  exit(EXIT_FAILURE);
}
