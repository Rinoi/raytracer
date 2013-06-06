/*
** seek_mat.c for raytracer in /home/mart_p//raytracer/new_elem
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Thu Jun  6 15:26:59 2013 louis martin-pierrat
** Last update Thu Jun  6 15:27:16 2013 louis martin-pierrat
*/
#include	"rt.h"

t_mat		*seek_mat(int mat_id, t_mat *mat)
{
  t_mat		*tmp;

  tmp = mat;
  while (tmp != NULL && tmp->id != mat_id)
    tmp = tmp->next;
  return (tmp);
}
