/*
** my_getfloat.c for my_getfloat.c in /home/mayol_l//Wolf3D
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Jan  2 17:17:46 2013 lucas mayol
** Last update Sun May 12 22:56:10 2013 lucas mayol
*/

#include <stdio.h>
#include <stdlib.h>

int     my_getnbr(char *str);

/* float	my_getfloat(char *str) */
/* { */
/*   float	e; */
/*   float	d; */
/*   int	i; */
/*   float	my_return; */

/*   i = 1; */
/*   e = my_getnbr(str); */
/*   while (*str >= '0' && *str <= '9' && *str != '\0') */
/*     str = str + 1; */
/*   if (*str == '.') */
/*     str = str + 1; */
/*   if (*str == '0') */
/*     i = i * 10; */
/*   while (*str == '0') */
/*     { */
/*       str = str + 1; */
/*       i = i * 10; */
/*     } */
/*   d = my_getnbr(str); */
/*   while (d / i > 10) */
/*     i = i * 10; */
/*   i = i * 10; */
/*   my_return = e + (d / i); */
/*   return (my_return); */
/* } */

float		my_getfloat(char *str)
{
  return (atof(str));
}
