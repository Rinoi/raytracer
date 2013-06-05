/*
** f_error.c for cluster in /home/mart_q//cluster/server/src
** 
** Made by thibault martinez
** Login   <mart_q@epitech.net>
** 
** Started on  Fri May 31 12:39:10 2013 thibault martinez
** Last update Wed Jun  5 20:01:14 2013 thibault martinez
*/

#include	"network.h"

void		f_error(char *msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}
