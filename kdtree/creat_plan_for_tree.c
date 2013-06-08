/*
** creat_plan_for_tree.c for RT in /home/mayol_l//git/Raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 14 20:22:35 2013 lucas mayol
** Last update Sat Jun  8 23:47:48 2013 lucas mayol
*/

#include <stdlib.h>
#include <stdio.h>
#include "rt.h"

void    creat_plan_for_tree(t_kdtree *tree)
{
  tree->plan.ptn.x = MAXDOUBLE;
  tree->plan.ptn.y = MAXDOUBLE;
  tree->plan.ptn.z = MAXDOUBLE;
  if (tree->pr % 3 == 0)
    {
      tree->plan.ptn.x = tree->ori.x + ((sqrt(pow(tree->max.x - tree->ori.x, 2))) / 2);
      //      printf("PLAn X : \n");
    }
  else if (tree->pr % 3 == 1)
    {
      tree->plan.ptn.y = tree->ori.y + ((sqrt(pow(tree->max.y - tree->ori.y, 2))) / 2);
      // printf("PLAn Y : \n");
    }
  else
    {
      tree->plan.ptn.z = tree->ori.z + ((sqrt(pow(tree->max.z - tree->ori.z, 2))) / 2);
      // printf("PLAn Z : \n");
    }
  // printf("\tPLAN = x : %f, y : %f, z : %f\n", tree->plan.ptn.x, tree->plan.ptn.y, tree->plan.ptn.z);
}
