/*
** rtv1.h for rtv1 in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Feb  6 11:20:24 2013 lucas mayol
*/

#ifndef _RTV_
# define _RTV_

# include <pthread.h>
# include <math.h>
# include <values.h>
# include "mlx.h"
# include "kdtree.h"

# define RAD(x)		(M_PI * (x) / 180)
# define NOTINIT	0xFFFFFFFF
# define EPSILLON	0.00001

typedef	struct	s_inter t_inter;
typedef struct	s_resource t_rs;

typedef	struct	s_straight
{
  float		power;
  int		x;
  int		y;
  t_ptn		vec;
  t_ptn		cord;
  t_ptn		c_kd;
} t_st;

typedef	struct	s_material
{
  int		id;
  float		red;
  float		green;
  float		blue;
  float		spec;
  float		spec_pow;
  float		reflex;
  float		trans;
  float		refract;
  float		diff_reflex;
  void		*img;
} t_mat;

typedef struct	s_lux
{
  t_ptn			cord;
  int			color;
  int			lux;
  struct s_lux		*next;
} t_lux;

typedef	struct	s_obj
{
  t_ptn		ptn;
  t_ptn		rot;
  void		*data;
  //  int		id;
  t_mat		*mat;
  float		*matrix;
  t_box		box;
  t_ptn		*(*cal_inter)(struct s_obj *obj, t_st *dr);
  float		(*cal_lux_cos)(struct s_obj *obj, t_ptn *ptn, t_lux *lux);
  //  unsigned int	d[4];
  struct s_obj	*next;
} t_obj;

typedef	struct	s_inter
{
  t_ptn		*(*cal_norm)(struct s_obj *obj, t_ptn *ptn);
  t_obj		*obj;
  t_ptn		ptn;
  float		dist;
  double	d;
  int		color;
} t_inter;

typedef struct	s_img
{
  char		*img;
  int		x;
  int		y;
  void		*img_ptr;
  int		endian;
  int		bpp;
  int		sizeline;
} t_img;

typedef struct	s_wind
{
  t_img		img;
  int		x;
  int		y;
  void		*wind_ptr;
  void		*mlx_ptr;
} t_wind;

typedef struct	s_environnement
{

} t_env;

typedef struct	s_pov
{
  t_ptn		cam;
  t_ptn		rot;
  int		larg;
  int		lng;
  struct s_pov	*next;
} t_pov;

typedef struct	s_resource
{
  t_obj		*obj;
  t_obj		*obj_inf;
  t_lux		*lux;
  //  t_env		*bckground;
  void		*aff;
  void		*send_rayon;
  t_wind	wind;
  t_kdtree	*tree;
  t_pov		*eyes;
  //  t_ptn		eyes;
  //  int		l;
} t_rs;

/* void	multipli_x(t_ptn *ptn, float angle); */
/* void	multipli_y(t_ptn *ptn, float angle); */
/* void	multipli_z(t_ptn *ptn, float angle); */
/* t_ptn	*my_call_point_shere(t_obj *o, t_st *d); */
/* t_ptn	*my_call_point_triangle(t_obj *o, t_st *d); */
/* t_ptn	*my_call_point_conus(t_obj *o, t_st *d); */
/* t_ptn	*my_call_point_cylinder(t_obj *o, t_st *d); */
/* void	my_take_data_for_rs(t_rs *rs, int fd); */
/* int	my_strlen(char *str); */
/* void	rtv1_main(t_rs *rs); */
/* void	my_putchar(char c, int fd); */
/* void	my_putstr(char *str, int fd); */
/* int	my_getnbr(char *str); */
/* float	my_getfloat(char *str); */
/* float	my_get_dn(char *str, char *name); */
/* void	boxin_cone(t_obj *obj); */
/* void	boxin_cylindre(t_obj *obj); */
/* void	boxin_sphere(t_obj *obj); */
/* void	boxin_triangle(t_obj *obj); */
/* void	rt_main(t_rs *rs); */
/* int	my_expose(t_rs *rs); */
/* void	send_rayon_main(t_rs *rs); */
/* void	my_pixel_put_to_image(t_img *img, int x, int y, unsigned int color); */
/* float	my_call_dist(t_ptn *ptn1, t_ptn *ptn2); */
/* t_inter	*my_send_rayon_act_kdtree(t_rs *rs, t_st *droite); */
/* unsigned int	my_cal_lux(t_rs *rs, t_inter *inter); */
/* float	my_cal_lux_cos_shere(t_obj *obj, t_ptn *ptn, t_lux *lum); */
/* float	my_cal_lux_cos_triangle(t_obj *obj, t_ptn *ptn, t_lux *lum); */
/* float	my_cal_lux_cos_conus(t_obj *obj, t_ptn *ptn, t_lux *lum); */
/* float	my_cal_lux_cos_cylinder(t_obj *obj, t_ptn *ptn, t_lux *lum); */
/* t_ptn	*cal_norm_triangle(t_obj *obj, __attribute__((unused)) t_ptn *ptn); */
/* t_ptn	*cal_norm_shere(t_obj *obj, t_ptn *ptn); */
/* t_ptn	*cal_norm_conus(t_obj *o, t_ptn *p); */
/* t_ptn	*cal_norm_cylinder(t_obj *o, t_ptn *p); */
/* double	*matrice_rot(double a, double x, double y, double z); */
/* t_ptn	*mul_matrice(double *matrice, t_ptn *ptn); */

// SRC                                                                                                                                                                                              
// my_put.c                                                                                                                                                                                                         
int             my_strlen(char *);
void            my_putchar(char, int);
void            my_putstr(char *, int);

// MLX                                                                                                                                                                                              
// wind.c                                                                                                                                                                                                           
void            rt_main_mlx(t_rs *);

//my_pixel_put_to_image.c  

void		my_pixel_put_to_image(t_img *, int, int, unsigned int);

double	*creat_matrice();
double	*matrice_translat(double x, double y, double z);
double	*matrice_homo(double x, double y, double z);
double	*matrice_rot_x(double angle);
double	*matrice_rot_y(double angle);
double	*matrice_rot_z(double angle);

void	rt_main_mlx(t_rs *rs);

void	ini_mlx(t_rs *rs);

#endif
