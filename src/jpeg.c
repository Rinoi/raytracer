/*
** jpeg.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  2 20:31:41 2013 karina martynava
** Last update Thu Jun  6 18:10:48 2013 thibault martinez
*/

#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include "rt.h"

# define JPEG_QUALITY	100

void		get_col_componnent(char col[3], int x, int y, t_rs *rs)
{
  int		color;
  unsigned char	*modif;

  color = get_img_color(&(rs->wind.sampled), x, y);
  modif = (unsigned char *)&color;
  col[0] = modif[2];
  col[1] = modif[1];
  col[2] = modif[0];
}

void		record_color_for_jpeg(int cord[2], struct jpeg_compress_struct *cinfo,
				      unsigned char *image_buffer, t_rs *rs)
{
  unsigned int	pixelIdx;
  char		col[3];
  int		x;
  int		y;

  x = cord[1] - 1;
  y = cord[0] - 1;
  pixelIdx = ((y * cinfo->image_height) + x) * cinfo->input_components;
  get_col_componnent(col, x, y, rs);
  image_buffer[pixelIdx + 0] = col[0];
  image_buffer[pixelIdx + 1] = col[1];
  image_buffer[pixelIdx + 2] = col[2];
}

void		img_creation(struct jpeg_compress_struct *cinfo,
			     JSAMPROW row_pointer[1], t_rs *rs)
{
  unsigned char *image_buffer;
  int		cord[2];
  int		row_stride;

  image_buffer =
    (unsigned char *)malloc(cinfo->image_width * \
			    cinfo->image_height * cinfo->num_components);
  if (image_buffer == NULL)
    {
      my_putstr("JPEG creation : malloc failed\n", 2);
      return ;
    }
  cord[0] = 0;
  while (cord[0]++ < rs->eyes->lng && (cord[1] = 0) == 0)
    while (cord[1]++ < rs->eyes->larg)
      record_color_for_jpeg(cord, cinfo, image_buffer, rs);
  jpeg_start_compress(cinfo, TRUE);
  row_stride = cinfo->image_width * 3;
  while (cinfo->next_scanline < cinfo->image_height)
    {
      row_pointer[0] = &image_buffer[cinfo->next_scanline * row_stride];
      (void)jpeg_write_scanlines(cinfo, row_pointer, 1);
    }
}

void	jpeg_creation(t_rs *rs)
{
  struct jpeg_compress_struct	cinfo;
  struct jpeg_error_mgr		jerr;
  FILE				*outfile;
  JSAMPROW			row_pointer[1];
 
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  if ((outfile = fopen("rt.jpeg", "wb")) == NULL)
    {
      my_putstr("JPEG creation : open failed\n", 2);
      return ;
    }
  jpeg_stdio_dest(&cinfo, outfile);
  cinfo.image_width  = rs->eyes->larg;
  cinfo.image_height = rs->eyes->lng;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, JPEG_QUALITY, TRUE);
  img_creation(&cinfo, row_pointer, rs); 
  jpeg_finish_compress(&cinfo);
  fclose(outfile);
  jpeg_destroy_compress(&cinfo);
  my_putstr("L'image a été sauvegardée sous format JPEG.\n", 1);
}
