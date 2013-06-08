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
# include "xml.h"
# include "bruit.h"

# define RAD(x)		(M_PI * (x) / 180)
# define NOTINIT	0xFFFFFFFF
# define SIZE_LARG	1000
# define SIZE_LONG	1000

// FOR INTERSECTIONS
# define EPSILLON	0.0001

// LUM
# define NONE		0
# define AMB		1
# define SPOT		2
# define DIRECT		4
# define SPOTLEN	10

// POST - IN PROCESSING
# define ANTIA		2
# define MAXDEPTH	10
# define EXPO		-2.07f
# define B_AND_W	0
# define SEPIA		0
# define NEGATIVE	0
# define SEP_RED	112.0
# define SEP_GREEN	66.0
# define SEP_BLUE	20.0
# define STEREOSCOPY	0
# define GO_OUT		1
# define GO_IN		0
# define DEFAULT_INDICE	1.0f
# define DEF_FOCUS	50.0f
# define COMPLEXITY	1
# define DISPER		1.0f
# define SPACE		1.0f

typedef	struct	s_inter t_inter;
typedef struct	s_resource t_rs;
typedef struct	s_obj t_obj;
typedef struct	s_fresnel t_fresnel;

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

typedef struct	s_neg
{
  float		deb;
  float		end;
  t_obj		*obj;
  struct s_neg	*next;;
} t_neg;

typedef	struct	s_straight
{
  float		power;
  int		x;
  int		y;
  float		indice;
  t_fresnel	*ind_list;
  t_ptn		vec;
  t_ptn		cord;
  t_ptn		c_kd;
  t_neg		*neg;
} t_st;

typedef struct 	s_bruit
{
  int		type;
  float		persistance;
  float		color1[3];
  float		color2[3];
} t_bruit;

typedef	struct		s_material
{
  int			id;
  int			damier;
  float			red;
  float			green;
  float			blue;
  float			spec[3];
  float			spec_pow;
  float			reflex;
  float			bump;
  float			trans;
  float			indice;
  t_img			img;
  t_bruit		bruit;
  struct s_material	*next;
} t_mat;

typedef struct	s_lux
{
  int		attribute;
  t_ptn		cord;
  int		color;
  float		red;
  float		green;
  float		blue;
  float		lux;
  struct s_lux	*next;
} t_lux;

typedef	struct	s_tri
{
  int		color[3];
  t_ptn		nrml[3];
  t_ptn		a2;
  t_ptn		a3;
} t_tri;

typedef	struct	s_obj
{
  int		id;
  t_ptn		ptn;
  t_ptn		rot;
  void		*data;
  t_mat		*mat;
  double       	*matrix;
  double       	*matrix_inv;
  float		limit_z;
  t_box		box;
  t_inter      	*(*cal_inter)(struct s_obj *, t_st );
  float		(*cal_lux_cos)(struct s_obj *, t_ptn *, t_lux *);
  void		(*cal_color)(struct s_obj *, t_inter *, float *);
  struct s_obj	*next;
} t_obj;

typedef	struct	s_inter
{
  t_ptn		*(*cal_norm)(struct s_obj *obj, t_ptn *ptn);
  t_obj		*obj;
  t_ptn		ptn;
  t_ptn		rela_ptn;
  t_ptn		ori_ptn;
  float		dist;
  int		status;
  double	d;
  int		color;
} t_inter;

typedef struct	s_wind
{
  t_img		sampled;
  int		x;
  int		y;
  void		*wind_ptr;
  void		*mlx_ptr;
} t_wind;

typedef struct	s_environnement
{
  int		antia;
  int		b_and_w;
  int		sepia;
  int		negative;
  int		pattern;
  float		expo;
  int		complexity;
  float		disper;
  float		focus;
  int		stereo;
} t_env;

typedef struct	s_pov
{
  t_ptn		cam;
  t_ptn		rot;
  double	*matrix;
  int		larg;
  int		lng;
  struct s_pov	*next;
} t_pov;

typedef struct	s_resource
{
  int		thr;
  int		client;
  t_obj		*obj;
  t_obj		*obj_neg;
  t_lux		*lux;
  t_img		bckground;
  t_env		env;
  void		*aff;
  void		*send_rayon;
  t_wind	wind;
  t_kdtree	*tree;
  t_pov		*eyes;
  t_mat		*mat;
} t_rs;

typedef struct	s_patterns
{
  int		num;
  void		(*ptr)(t_data_t *, t_st *);
} t_patterns;

typedef struct	s_fresnel
{
  float			indice;
  t_mat			*mat;
  struct s_fresnel	*next;
  struct s_fresnel	*prev;
} t_resnel;
int     init_rs(t_rs *rs, struct s_xml *tree);

// color.c

int	convert_col(float col[3]);

// lum.c

void	enligten(t_inter *point, t_rs *rs, float col[4], t_st *st);

// reflexion.c

void	col_update_reflex(float col[4], float tmp_col[4], t_inter *inter, t_st *st);

// send_rayon.c

t_inter	*my_send_rayon_act(t_rs *rs, t_st *droit);
void	my_send_rayon(t_rs *rs, t_st *droit, float col[4]);

// my_put.c

int     my_strlen(char *);
void    my_putchar(char, int);
void    my_putstr(char *, int);

// vect_op.c

float	scal_prod(t_ptn *, t_ptn *);
void	sub_vect(t_ptn *, t_ptn *, t_ptn *);
void	add_vect(t_ptn *, t_ptn *, t_ptn *);
void	mult_vect(t_ptn *, float);

// patterns.c

void	alea_pattern(t_data_t *data, t_st *droit);
void	nrml_pattern(t_data_t *data, t_st *droit);
void	vert_pattern(t_data_t *data, t_st *droit);

// anti aliasing

int	antialiasing_color(int antialias, t_st *droit, t_rs *rs, float focus[COMPLEXITY][2]);

// MLX

// wind.c

void	rt_main_mlx(t_rs *);
int     my_expose(t_rs *rs);

//my_pixel_put_to_image.c  

void		my_pixel_put_to_image(t_img *, int, int, unsigned int);

// img

int     get_img_color(t_img *img, int x, int y);
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
void	creat_matrice_for_eyes(t_pov *obj);

void	rt_main_mlx(t_rs *rs);

void	ini_mlx(t_rs *rs);
void	*send_rayon_main_act(void *data);
void	send_rayon_main(t_rs *rs);

t_inter	*call_inter_sphere(t_obj *obj, t_st dr);
t_inter	*call_inter_cylinder(t_obj *obj, t_st dr);
t_inter	*call_inter_conus(t_obj *obj, t_st dr);
t_inter	*call_inter_plane(t_obj *obj, t_st dr);
t_inter	*call_inter_triangle(t_obj *o, t_st dr);

t_ptn	*sphere_nrml(t_obj *obj, t_ptn *ptn);
t_ptn	*sphere_nrml_inv(t_obj *obj, t_ptn *ptn);
t_ptn	*cylinder_nrml(t_obj *obj, t_ptn *ptn);
t_ptn	*cylinder_nrml_inv(t_obj *obj, t_ptn *ptn);
t_ptn	*conus_nrml(t_obj *obj, t_ptn *ptn);
t_ptn	*plane_nrml(t_obj *obj, t_ptn *ptn);
t_ptn	*plane_nrml_inv(t_obj *obj, t_ptn *ptn);
t_ptn	*triangle_nrml(t_obj *obj, t_ptn *ptn);

void	cal_color_cylinder(t_obj *obj, t_inter *inter, float *tab);
void	cal_color_plan(t_obj *obj, t_inter *inter, float tab[3]);
void	cal_color_shere(t_obj *obj, t_inter *inter, float tab[3]);
void	cal_color_conus(t_obj *obj, t_inter *inter, float tab[3]);
void	call_color_triangle(t_obj *obj, t_inter *inter, float tab[3]);
int	cal_texture_plan(t_obj *obj, float x, float y, float z);

float	resolve_two(float a, float b, float c, int *x);
float	resolve_two_inv(float a, float b, float c, int *x);

int	color_bruit_bois(t_obj *obj, t_inter *inter);
void	my_bump(t_ptn *nrml, t_ptn *ptn, float bump);

void	new_material(t_mat **, t_rs *, struct s_xml *);
void	new_eyes(t_pov **, struct s_xml *);
void	new_lux(t_lux **, struct s_xml *);
void	new_objs(t_rs *, struct s_xml *);
void	new_objs_neg(t_rs *, struct s_xml *);

void	new_sphere(t_obj **, t_mat *, struct s_xml *, int);
void	new_plane(t_obj **, t_mat *, struct s_xml *, int);
void	new_cylinder(t_obj **, t_mat *, struct s_xml *, int);
void	new_conus(t_obj **, t_mat *, struct s_xml *, int);
void	new_triangle(t_obj **, t_mat *, struct s_xml *, int);
void	set_env(t_env *, struct s_xml *);
void	new_extern(t_obj **, t_mat *, struct s_xml *, int);

void	add_to_end(t_obj **, t_obj *);
t_mat	*seek_mat(int, t_mat *);
int	is_in_neg(t_neg *obj, float d);
void	call_obj_neg(t_st *droit, t_rs *rs);
void	refraction(t_inter *inter, t_st *st);
float	lambert_coef(t_ptn *lightray, t_ptn *nrml, char attribute);
int	inlight(t_rs *rs, t_st *droit, float lux[3]);
void	blinn_phong(t_st *st, t_ptn *light,
		    t_inter *last, float col[4], t_lux *sv);
t_obj		*obj_pars_main(char *obj, t_obj *tmp);

#endif
