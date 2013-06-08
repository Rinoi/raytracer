/*
** antialiasing.c for rt in /home/martyn_k//raytracer/src
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  2 20:18:27 2013 karina martynava
** Last update Sat Jun  8 17:20:16 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

void	add_antialia(float final_col[3], float col[3])
{
  final_col[0] += col[0];
  final_col[1] += col[1];
  final_col[2] += col[2];
}

void	moving_straight(t_st *cpy, float focus[COMPLEXITY][2], int i, t_rs *rs)
{
  t_ptn	*mat;
  t_ptn	goal;

  mult_vect(&cpy->vec, 1.0f / sqrt(scal_prod(&cpy->vec, &cpy->vec)));
  goal.x = cpy->cord.x + DEF_FOCUS * cpy->vec.x;
  goal.y = cpy->cord.y + DEF_FOCUS * cpy->vec.y;
  goal.z = cpy->cord.z + DEF_FOCUS * cpy->vec.z;
  cpy->cord.y += focus[i - 1][0];
  cpy->cord.z += focus[i - 1][1];
  cpy->vec.x = goal.x - cpy->cord.x;
  cpy->vec.y = goal.y - cpy->cord.y;
  cpy->vec.z = goal.z - cpy->cord.z;
  mat = mul_m_p(rs->eyes->matrix, &cpy->vec);
  cpy->vec = *mat;
  free(mat);
}

void	focus_scene(t_st *st, t_rs *rs, float col[4],
		    float focus[COMPLEXITY][2])
{
  int	i;
  t_st	cpy;
  float	tmp_col[4];

  tmp_col[0] = 0;
  tmp_col[1] = 0;
  tmp_col[2] = 0;
  cpy = *st;
  i = 0;
  while (i++ < COMPLEXITY)
    {
      cpy = *st;
      moving_straight(&cpy, focus, i, rs);
      my_send_rayon(rs, &cpy, col);
      tmp_col[0] += col[0];
      tmp_col[1] += col[1];
      tmp_col[2] += col[2];
    }
  col[0] = tmp_col[0] / COMPLEXITY;
  col[1] = tmp_col[1] / COMPLEXITY;
  col[2] = tmp_col[2] / COMPLEXITY;
}

int	antialiasing_apply(int antialias, t_st *droit,
			   t_rs *rs, float focus[COMPLEXITY][2])
{
  int	i;
  int	j;
  float	final_col[4];
  float	col[4];
  float	antia;

  i = 0;
  final_col[0] = 0;
  final_col[1] = 0;
  final_col[2] = 0;
  antia = (antialias % 2 != 0 || antialias == 0) ? 1.0f : 1.0f / antialias;
  while (i++ < antialias && (j = 0) == 0)
    while (j < antialias)
      {
	droit->vec.x = rs->eyes->larg / 2;
	droit->vec.z = (rs->eyes->larg / 2 - droit->y + (i - 1) * antia);
	droit->vec.y = rs->eyes->larg / 2 - droit->x + j++ * antia;
	focus_scene(droit, rs, col, focus);
	add_antialia(final_col, col);
      }
  final_col[0] = final_col[0] * antia;
  final_col[1] = final_col[1] * antia;
  final_col[2] = final_col[2] * antia;
  return (convert_col(final_col));
}

int	antialiasing_color(int antialias, t_st *droit,
			   t_rs *rs, float focus[COMPLEXITY][2])
{
  int	col_1;
  int	col_2;
  int	return_col;
  t_st	cpy;
  unsigned char	*modif_1;
  unsigned char	*modif_2;
  unsigned char	*modif;

  if (STEREOSCOPY == 0)
    return (antialiasing_apply(antialias, droit, rs, focus));
  cpy = *droit;
  cpy.vec.y = cpy.vec.y - SPACE;
  cpy.cord.y += SPACE;
  col_1 = antialiasing_apply(antialias, &cpy, rs, focus);
  cpy = *droit;
  cpy.vec.y = cpy.vec.y + SPACE;
  cpy.cord.y -= SPACE;
  col_2 = antialiasing_apply(antialias, &cpy, rs, focus);
  modif_1 = (unsigned char *)&col_1;
  modif_2 = (unsigned char *)&col_2;
  modif = (unsigned char *)&return_col;
  modif[0] = modif_1[0];
  modif[1] = (modif_1[0] + modif_2[0]) / 2;
  modif[2] = modif_2[2];
  return (return_col);
}
