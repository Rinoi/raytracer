/*
** xml_getdirective.c for xml_parseur in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Sat Jun  1 17:42:42 2013 louis martin-pierrat
** Last update Mon Jun  3 19:00:12 2013 louis martin-pierrat
*/
#include	"xml_struct.h"
#include	"xml_define.h"
#include	"xml_macros.h"

int		xml_getdirective(const int fd)
{
  int		end;
  char		c;

  end = 0;
  while (xml_getchar(fd, &c) != FAILURE)
    {
      if (c == '>' && end == 1)
	return (SUCCESS);
      end = (c == '?' ? 1 : 0);
    }
  return (FAILURE);
}
