/*
** my_take_data.c for RT in /home/mayol_l//RT
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Apr 13 13:36:52 2013 lucas mayol
** Last update Sun May 19 01:00:56 2013 lucas mayol
*/

#include <stdlib.h>
#include "../include/rtv1.h"
#include "../pars/pars.h"

void	my_take_data_for_rs(t_rs *rs, int fd)
{
  t_noeud       n;

  rs->obj = NULL;
  rs->obj_inf = NULL;
  pars_main(rs, fd, &n);
  my_rec_dn(rs, &n);
}
