/*
** xmalloc.c for xmalloc in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Mon Jun  3 17:14:42 2013 louis martin-pierrat
** Last update Mon Jun  3 17:16:05 2013 louis martin-pierrat
*/
#include	<stdlib.h>
#include	<unistd.h>

void		*xmalloc(size_t size)
{
  void		*ret;

  if ((ret = malloc(size)) == NULL)
    {
      write(STDERR_FILENO, "Memory allocation failed\n", 25);
      exit(EXIT_FAILURE);
    }
  return (ret);
}
