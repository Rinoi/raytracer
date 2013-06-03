/*
** xml_struct.h for xml_parsing in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Sat Jun  1 01:14:54 2013 louis martin-pierrat
** Last update Mon Jun  3 15:27:29 2013 louis martin-pierrat
*/

#ifndef		__XML_STRUCT__
#define		__XML_STRUCT__

struct s_xml
{
  char		*name;
  char		*attributes;
  char		*value;
  struct s_xml	*parent;
  struct s_xml	*child;
  struct s_xml	*prev;
  struct s_xml	*next;
};

#endif
