/*
** xml_select.c for xml_parseur in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Mon Jun  3 18:42:50 2013 louis martin-pierrat
** Last update Mon Jun  3 18:55:44 2013 louis martin-pierrat
*/
#include	"xml_struct.h"
#include	"xml_define.h"
#include	"xml_macros.h"

int		xml_select(const int fd, struct s_xml **tree, char c)
{
  if (c != '<' || xml_getchar(fd, &c) == FAILURE)
    return (ERROR);
  if (c == '?')
    return (xml_getdirective(fd));
  else if (c == '!')
    return (xml_getcom(fd, c));
  else if (c == '/')
    return (xml_getendtag(fd, tree));
  return (xml_gettag(fd, tree, c));
}
