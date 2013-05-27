##
## Makefile for Raytracing in /home/mayol_l//git/RayTracer
## 
## Made by lucas mayol
## Login   <mayol_l@epitech.net>
## 
## Started on  Sat May 11 02:21:08 2013 lucas mayol
## Last update Tue May 28 01:17:53 2013 louis martin-pierrat
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
		mlx/my_pixel_put_to_image.c \
		mlx/wind.c

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		gcc -g $(FLAG) $(OBJS) -o $(NAME) $(LIBS)

clean: 
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all