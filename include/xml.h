/*
** xml.h for xml in /home/mart_p//raytracer
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Mon Jun  3 20:54:13 2013 louis martin-pierrat
** Last update Wed Jun  5 20:54:16 2013 louis martin-pierrat
*/

#ifndef		__XML__
#define		__XML__

#include	"xml_struct.h"
#include	"xml_define.h"
#include	"xml_macros.h"

int		get_fvalue(struct s_xml *, char *, float *);
int		get_ivalue(struct s_xml *, char *, int *);
int		get_fvalues(struct s_xml *, char *, char *, float *);
int		get_ivalues(struct s_xml *, char *, char *, int *);
int		get_strvalue(struct s_xml *, char *, char **);

#endif
