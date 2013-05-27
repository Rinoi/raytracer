/*
** my_pars_scene.c for pars_xml in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Feb 20 00:31:17 2013 lucas mayol
** Last update Sat Apr 13 13:11:53 2013 lucas mayol
*/

#include <stdlib.h>
#include "../include/rtv1.h"
#include "../include/get_next_line.h"
#include "pars.h"

void		pars_main(t_rs *rs, int fd, t_noeud *n)
{
  pars_main_tree(rs, fd, n);
}
