/*
** xml_define.h for xml_parsing in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Sat Jun  1 01:15:49 2013 louis martin-pierrat
** Last update Tue Jun  4 17:38:58 2013 louis martin-pierrat
*/

#ifndef		__XML_DEFINE__
#define		__XML_DEFINE__

int		xml_getattribute(const int, struct s_xml **);
int		xml_getvalues(const int, struct s_xml **);
int		xml_gettag(const int, struct s_xml **, char);
int		xml_select(const int, struct s_xml **, char);
int		xml_getchar(const int, char *);
int		xml_getspace(const int, char *);
int		xml_getdirective(const int);
int		xml_getcom(const int, char);
int		xml_getstr(const int, char *, int *);
void		*xmalloc(int);
int		xml_getendtag(const int, struct s_xml **);
struct s_xml	*xml_parsing(char *);
int		m_strcmp(char *, char *);
int		get_values(struct s_xml *, char *, char *, void *);
int		get_value(struct s_xml *, char *, void *);

#endif
