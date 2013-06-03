/*
** xml_getcom.c for xml_parseur in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Sat Jun  1 19:22:47 2013 louis martin-pierrat
** Last update Mon Jun  3 18:56:51 2013 louis martin-pierrat
*/
#include	"xml_struct.h"
#include	"xml_define.h"
#include	"xml_macros.h"

int		xml_getcom(const int fd, char c)
{
  int		end;

  end = 0;
  while (xml_getchar(fd, &c) != FAILURE)
    {
      if (c == '-' && (end == 0 || end == 1))
	end++;
      else if (c == '>' && end == 2)
	return (SUCCESS);
      else
	end = 0;
    }
  return (FAILURE);
}
