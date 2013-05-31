##
## Makefile for Raytracing in /home/mayol_l//git/RayTracer
## 
## Made by lucas mayol
## Login   <mayol_l@epitech.net>
## 
## Started on  Sat May 11 02:21:08 2013 lucas mayol
## Last update Sat Jun  1 01:33:05 2013 karina martynava
##

CC	=	gcc

CFLAGS	=	$(INC) -g -W -Wall -Wextra #-Werror -g #-O3

LIBS	=	-L/usr/lib64 -lmlx_$(HOSTTYPE) \
		-L/usr/lib64/X11 -lXext -lX11 -lm \
		-lpthread

NAME	=	rt

RM	=	rm -f

INC	=	-I./include

SRCS	=	src/main.c \
		src/my_put.c \
		src/send_rayon_main.c \
		src/lum.c \
		src/color.c \
		src/vect_op.c \
		src/reflexion.c \
		mlx/my_pixel_put_to_image.c \
		mlx/wind.c \
		mlx/img.c \
		mlx/supersampl.c \
		calc/resolve_two.c \
		calc/resolve_bis.c \
		calc/resolve_three.c \
		src/sphere/call_inter.c \
		src/cylinder/call_inter.c \
		src/conus/call_inter.c \
		src/plane/call_inter.c \
		src/sphere/nrml.c \
		src/cylinder/nrml.c \
		src/conus/nrml.c \
		src/plane/nrml.c \
		src/cylinder/cal_color.c \
		src/plane/call_color.c \
		matrice/creat_matrice.c \
		matrice/creat_matrice_spe.c \
		matrice/opération.c \
		matrice/matrice_dumb.c \
		matrice/creat_matrice_rot.c

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		gcc -g $(FLAG) $(OBJS) -o $(NAME) $(LIBS)

clean: 
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all