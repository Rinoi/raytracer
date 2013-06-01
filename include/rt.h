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

// FOR INTERSECTIONS
# define EPSILLON	0.0001

// LUM
# define NONE		0
# define AMB		1
# define SPOT		2
# define SPOTLEN	5

// POST - IN PROCESSING
# define ANTIA		2
# define MAXDEPTH	10
# define EXPO		-0.66f
# define B_AND_W	0
# define SEPIA		0
# define SEP_RED	112.0
# define SEP_GREEN	66.0
# define SEP_BLUE	20.0

typedef	struct	s_inter t_inter;
typedef struct	s_resource t_rs;

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
  float		spec[3];
  float		spec_pow;
  float		reflex;
  float		trans;
  float		refract;
  float		diff_reflex;
  t_img		img;
} t_mat;

typedef struct	s_lux
{
  char		attribute;
  t_ptn		cord;
  int		color;
  float		red;
  float		green;
  float		blue;
  float		lux;
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
  double       	*matrix_inv;
  t_box		box;
  t_inter      	*(*cal_inter)(struct s_obj *obj, t_st dr);
  float		(*cal_lux_cos)(struct s_obj *obj, t_ptn *ptn, t_lux *lux);
  void		(*cal_color)(struct s_obj *obj, t_inter *inter, float *retour);
  //  unsigned int	d[4];
  struct s_obj	*next;
} t_obj;

typedef	struct	s_inter
{
  t_ptn		*(*cal_norm)(struct s_obj *obj, t_ptn *ptn);
  t_obj		*obj;
  t_ptn		ptn;
  t_ptn		rela_ptn;
  float		dist;
  double	d;
  int		color;
} t_inter;

typedef struct	s_wind
{
  t_img		img;
  t_img		sampled;
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
  int		thr;
  t_obj		*obj;
  t_obj		*obj_inf;
  t_lux		*lux;
  t_img		bckground;
  void		*aff;
  void		*send_rayon;
  t_wind	wind;
  t_kdtree	*tree;
  t_pov		*eyes;
  t_mat		*mat;
  //  t_ptn		eyes;
  //  int		l;
} t_rs;

// color.c

int	convert_col(float col[3]);

// lum.c

void	enligten(t_inter *point, t_rs *rs, float col[4], t_st *st);

// reflexion.c

void	col_update_reflex(float col[4], float tmp_col[4], t_inter *inter, t_st *st);

// send_rayon.c

t_inter	*my_send_rayon_act(t_rs *rs, t_st *droit);
void	my_send_rayon(t_rs *rs, t_st *droit);

// my_put.c

int     my_strlen(char *);
void    my_putchar(char, int);
void    my_putstr(char *, int);

// vect_op.c

float	scal_prod(t_ptn *, t_ptn *);
void	sub_vect(t_ptn *, t_ptn *, t_ptn *);
void	add_vect(t_ptn *, t_ptn *, t_ptn *);
void	mult_vect(t_ptn *, float);

// MLX

// wind.c

void	rt_main_mlx(t_rs *);

//my_pixel_put_to_image.c  

void		my_pixel_put_to_image(t_img *, int, int, unsigned int);

// img

int	get_col(t_img *tex, int x, int y);
void	load_img(t_rs *rs, t_img *text, char *str);

// sampl
void	mlx_supersamp(t_rs *rs, int init, int to);

// matrice.h

void	change_dr(t_obj *obj, t_st *dr);
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
t_inter	*call_inter_conus(t_obj *obj, t_st dr);
t_inter	*call_inter_plane(t_obj *obj, t_st dr);

t_ptn	*sphere_nrml(t_obj *obj, t_ptn *ptn);
t_ptn	*cylinder_nrml(t_obj *obj, t_ptn *ptn);
t_ptn	*conus_nrml(t_obj *obj, t_ptn *ptn);
t_ptn	*plane_nrml(t_obj *obj, t_ptn *ptn);

void	cal_color_cylinder(t_obj *obj, t_inter *inter, float *tab);
void	cal_color_plan(t_obj *obj, t_inter *inter, float tab[3]);
int     cal_texture_plan(t_obj *obj, float x, float y, float z);

float	resolve_two(float a, float b, float c, int *x);

#endif
