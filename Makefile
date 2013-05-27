##
## Makefile for Raytracing in /home/mayol_l//git/RayTracer
## 
## Made by lucas mayol
## Login   <mayol_l@epitech.net>
## 
## Started on  Sat May 11 02:21:08 2013 lucas mayol
## Last update Mon May 27 11:57:24 2013 lucas mayol
##

CC	=	gcc $(CFLAG)

NAME	=	rt

RM	=	rm -f

CFLAG	=	$(INC) -g -W -Wall -Wextra #-Werror -g #-O3

INC	=	-Iinclude

SRCS	=	src/main.c \
		obj_pars/wrd_tab.c \
		src/rt_main.c \
		src/send_rayon_main.c \
		src/my_send_rayon_kdtree_hold.c \
		src/my_take_data.c \
		src/my_put.c \
		src/get_next_line.c \
		pars/pars_arbre.c \
		pars/pars_main_e.c \
		pars/my_error.c \
		pars/my_strcmp.c \
		pars/what_balist.c \
		pars/my_end_balist.c \
		pars/str_word.c \
		pars/my_pars_scene.c \
		kdtree/creat_tree.c \
		kdtree/creat_tree_e.c \
		kdtree/creat_plan_for_tree.c \
		src/cylinder/call_inter.c \
		src/cylinder/call_norm.c \
		src/cylinder/call_lux_cos.c \
		src/conus/call_inter.c \
		src/conus/call_lux_cos.c \
		src/conus/call_norm.c \
		src/shere/call_inter.c \
		src/shere/call_lux_cos.c \
		src/triangle/call_inter.c \
		src/triangle/call_lux_cos.c \
		src/triangle/call_norm.c \
		src/my_getnbr.c \
                src/my_getfloat.c \
		src/my_take_obj.c \
		src/my_take_lum.c \
		src/my_conf_elemn.c \
		src/my_get_dn.c \
		src/my_rec_dn.c \
		src/boxing.c \
		src/rotate.c \
		src/my_pixel_put_to_image.c \
		src/my_call_dist.c \
		src/my_cal_lux.c \

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		gcc -g $(FLAG) $(OBJS) -o $(NAME) \
-L/usr/lib64 -lmlx_$(HOSTTYPE) \
-L/usr/lib64/X11 -lXext -lX11 -lm \
-lpthread
clean: 
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all