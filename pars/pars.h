/*
** pars.h for pars in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue Feb 19 22:42:11 2013 lucas mayol
** Last update Fri May 10 18:32:35 2013 lucas mayol
*/

#ifndef _PAR_XML_
#define _PAR_XML_

# include "../include/rtv1.h"

# define SCENE		"scene"
# define SPHERE		"sphere"
# define CONUS		"conus"
# define CUBE		"cube"
# define TORE		"tore"
# define H_CUBE		"holed_cube"
# define PLANE		"plane"
# define CYLINDER	"cylinder"
# define TRIANGLE	"triangle"
# define NB_DIFF_OBJ	5

typedef struct s_fct_elem
{
  int	(*ptr)(t_obj *);
  char	*str;
} t_fct_elem;

typedef	struct	s_balist
{
  int		bool;
  char		*name;
  char		**arg;
  char		*data;
} t_balist;

typedef	struct	s_lb
{
  t_balist	bal;
  int		boll;
  char		*data;
  struct s_lb	*lb;
  struct s_lb	*next;
} t_lb;

typedef struct	s_feuille
{
  int		type;
  char		*data;
} t_feuille;

typedef struct		s_noeud
{
  int			type;
  char			*pres;
  t_balist		bal;
  struct s_noeud	*branche1;
  struct s_noeud	*branche2;
} t_noeud;

int	what_balist(char *str, t_balist *bal);
int	my_str_word(char *str);
int	my_strcmp(char *str, char *cmp);
void	my_error(t_rs *rs, char *str);
void	my_pars_scene(t_rs *rs, char *str);
char	*my_take_word(char *str, int *u);
int	my_end_balist(char *str, t_balist *bal, int u);
void	pars_main_tree(t_rs *rs, int fd, t_noeud *n);
char	*my_pars_act(t_rs *rs, int fd, t_noeud *lb, char *str);
void	pars_main(t_rs *rs, int fd, t_noeud *n);
void	my_rec_dn(t_rs *rs, t_noeud *n);
void	my_take_obj(t_rs *rs, t_noeud *n);
void	my_take_lum(t_rs *rs, t_noeud *n);
int	epure_to_next(char *str);
char	*my_go_to_next(t_rs *rs, char *str, int fd);
char	*my_take_data(t_rs *rs, t_lb *lb, char *str, int fd);
int	my_conf_elem(t_obj *elem, t_noeud *n);

#endif
