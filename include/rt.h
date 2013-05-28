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

typedef struct	s_data_t
{
  int		ini;
  int		max;
  t_rs		*rs;
} t_data_t;

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
  t_ptn		cord;
  int		color;
  float		red;
  float		green;
  float		blue;
  int		lux;
  struct s_lux	*next;
} t_lux;

typedef	struct	s_obj
{
  t_ptn		ptn;
  t_ptn		rot;
  void		*data;
  //  int		id;
  t_mat		*mat;
  double       	*matrix;
  t_box		box;
  t_inter      	*(*cal_inter)(struct s_obj *obj, t_st dr);
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

// my_put.c

int             my_strlen(char *);
void            my_putchar(char, int);
void            my_putstr(char *, int);

// vect_op.c

float	scal_prod(t_ptn *, t_ptn *);
void	sub_vect(t_ptn *, t_ptn *, t_ptn *);
void	add_vect(t_ptn *, t_ptn *, t_ptn *);

// MLX

// wind.c

void	rt_main_mlx(t_rs *);

//my_pixel_put_to_image.c  

void		my_pixel_put_to_image(t_img *, int, int, unsigned int);

// matrice.h

double	*creat_matrice();
double	*matrice_translat(double x, double y, double z);
double	*matrice_homo(double x, double y, double z);
double	*matrice_rot_x(double angle);
double	*matrice_rot_y(double angle);
double	*matrice_rot_z(double angle);
t_ptn	*mul_m_p(double *matrice, t_ptn *ptn);
double	*mul_matrice(double *m1, double *m2);
void	creat_matrice_for_obj(t_obj *obj);

void	rt_main_mlx(t_rs *rs);

void	ini_mlx(t_rs *rs);
void	*send_rayon_main_act(void *data);
void	send_rayon_main(t_rs *rs);
t_inter	*call_inter_sphere(t_obj *obj, t_st dr);
t_inter	*call_inter_cylinder(t_obj *obj, t_st dr);
float	resolve_two(float a, float b, float c, int *x);

#endif
