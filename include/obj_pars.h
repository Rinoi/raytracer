/*
** obj_pars.h for rt in /home/martyn_k//svn/Raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sat May 11 20:09:42 2013 karina martynava
** Last update Sun Jun  9 08:50:53 2013 karina martynava
*/

#ifndef __PARS_OBJ_FILE__
#define __PARS_OBJ_FILE__

typedef	struct		s_vortex
{
  int			i;
  int			total;
  float			ptn[99][3];
  struct s_vortex	*nxt;
  struct s_vortex	*prv;
} t_vr;

typedef struct s_ext
{
  t_obj	*obj;
  t_ptn	ptn;
  t_ptn	rot;
  int	fd;
} t_ext;

typedef struct s_obj_pars_cmd
{
    char  *str;
    void  (*ptr)(t_ext *, t_vr **, char **);
} t_obj_cmd;

char	**wrd_tab(char *str, char c);

#endif
