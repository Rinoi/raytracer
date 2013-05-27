/*
** my_call_dist.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Mon May  6 13:57:10 2013 lucas mayol
** Last update Mon May  6 13:59:28 2013 lucas mayol
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/rtv1.h"

float	my_call_dist(t_ptn *ptn1, t_ptn *ptn2)
{
  return (sqrt(pow(ptn2->x - ptn1->x, 2)
	       + pow(ptn2->y - ptn1->y, 2)
	       + pow(ptn2->z - ptn1->z, 2)));
}
