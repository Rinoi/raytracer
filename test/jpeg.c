/*
** jpeg.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  2 20:31:41 2013 karina martynava
** Last update Sun Jun  2 21:52:44 2013 karina martynava
*/


#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include "rt.h"

//-----------------------------
 
/* int main(t_rs *rs) */
/* { */
/*   char *filename = (char *)"test_jpeg.jpg"; */
/*   int quality    = 50; */
 
/*   struct jpeg_compress_struct cinfo;    // basic info for JPEG properties */
/*   struct jpeg_error_mgr jerr;           // in case of error */
/*   FILE * outfile;                       // target file */
/*   JSAMPROW row_pointer[1];              // pointer to JSAMPLE row[s] */
/*   int row_stride;                       // physical row width in image buffer */
 
/*   //## ALLOCATE AND INITIALIZE JPEG COMPRESSION OBJECT */
 
/*   cinfo.err = jpeg_std_error(&jerr); */
/*   jpeg_create_compress(&cinfo); */
 
/*   //## OPEN FILE FOR DATA DESTINATION: */
 
/*   if ((outfile = fopen(filename, "wb")) == NULL) { */
/*     fprintf(stderr, "ERROR: can't open %s\n", filename); */
/*     exit(1); */
/*   } */
/*   jpeg_stdio_dest(&cinfo, outfile); */
 
/*   //## SET PARAMETERS FOR COMPRESSION: */
 
/*   cinfo.image_width  = rs->eyes->larg;           // |-- image width and height in pixels */
/*   cinfo.image_height = rs->eyes->lng;           // | */
/*   cinfo.input_components = 3;         // number of color components per pixel */
/*   cinfo.in_color_space = JCS_RGB;     // colorspace of input image as RGB */
 
/*   jpeg_set_defaults(&cinfo); */
/*   jpeg_set_quality(&cinfo, quality, TRUE); */
 
 
/*   //## CREATE IMAGE BUFFER TO WRITE FROM AND MODIFY THE IMAGE TO LOOK LIKE CHECKERBOARD: */
 
/*   unsigned char *image_buffer = NULL; */
/*   image_buffer = (unsigned char*)malloc( cinfo.image_width*cinfo.image_height*cinfo.num_components ); */

/*   int	y; */
/*   int	x;  */

/*   y = 0; */
/*   while (y < cinfo.image_height) */
/*     { */
/*       x = 0; */
/*       while (x < cinfo.image_width) */
/* 	{ */
/* 	  unsigned int pixelIdx = ((y*cinfo.image_height)+x) * cinfo.input_components;  */
 
/* 	  if(x%2==y%2) */
/* 	    { */
/* 	      image_buffer[pixelIdx+0] = 255;   // r |-- set r,g,b components to */
/* 	      image_buffer[pixelIdx+1] = 0;     // g |   make this pixel red */
/* 	      image_buffer[pixelIdx+2] = 0;     // b |   (255,0,0) */
/* 	    } */
/* 	  else */
/* 	    { */
/* 	      image_buffer[pixelIdx+0] = 255;   // r |-- set r,g,b components to */
/* 	      image_buffer[pixelIdx+1] = 255;   // g |   make this pixel white */
/* 	      image_buffer[pixelIdx+2] = 255;   // b |   (255,255,255) */
/* 	    } */
/* 	  x++; */
/* 	}  */
/*       y++; */
/*     } */
 
/*   //## START COMPRESSION: */
 
/*   jpeg_start_compress(&cinfo, TRUE); */
/*   row_stride = cinfo.image_width * 3;        // JSAMPLEs per row in image_buffer */
 
/*   while (cinfo.next_scanline < cinfo.image_height) */
/*     { */
/*       row_pointer[0] = &image_buffer[cinfo.next_scanline * row_stride]; */
/*       (void) jpeg_write_scanlines(&cinfo, row_pointer, 1); */
/*     } */
/*   // NOTE: jpeg_write_scanlines expects an array of pointers to scanlines. */
/*   //       Here the array is only one element long, but you could pass */
/*   //       more than one scanline at a time if that's more convenient. */
 
/*   //## FINISH COMPRESSION AND CLOSE FILE: */
 
/*   jpeg_finish_compress(&cinfo); */
/*   fclose(outfile); */
/*   jpeg_destroy_compress(&cinfo); */
 
/*   printf("SUCCESS\n");   */
 
/*   exit(0); */
/* } */


# define JPEG_QUALITY	50

void		get_col_componnent(char col[3], int x, int y, t_rs *rs)
{
  int		color;
  unsigned char	*modif;

  color = get_img_color(&(rs->wind->sampled), x, y)
    modif = (unsigned char *)&color;
  col[0] = modif[0];
  col[1] = modif[1];
  col[2] = modif[2];
}

void		img_creation(struct jpeg_compress_struct cinfo,
			     JSAMPROW row_pointer[1], int row_stride)
{
  unsigned char *image_buffer;
  int		y;
  int		x; 
  unsigned int	pixelIdx;
  char		col[3];

  image_buffer = (unsigned char *)
    malloc(cinfo.image_width * cinfo.image_height * cinfo.num_components);
  if (image_buffer == NULL)
    {
      my_putstr("JPEG creation : malloc failed\n", 2);
      return ;
    }
  y = 0;
  while (y < cinfo.image_height && (x = 0) == 0)
    {
      while (x < cinfo.image_width)
	{
	  pixelIdx = ((y * cinfo.image_height) + x) * cinfo.input_components;
	  get_col_componnent(col, x++, y, rs);
	  image_buffer[pixelIdx + 0] = col[0];   // r |-- set r,g,b components to
	  image_buffer[pixelIdx + 1] = col[1];   // g |   make this pixel red
	  image_buffer[pixelIdx + 2] = col[2];   // b |   (255,0,0)
	} 
      y++;
    }
  jpeg_start_compress(&cinfo, TRUE);
  row_stride = cinfo.image_width * 3;
  while (cinfo.next_scanline < cinfo.image_height)
    {
      row_pointer[0] = &image_buffer[cinfo.next_scanline * row_stride];
      (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
}

void	jpeg_creation(t_rs *rs)
{
  struct jpeg_compress_struct	cinfo;		// basic info for JPEG properties
  struct jpeg_error_mgr		jerr;           // in case of error
  FILE				*outfile;       // target file
  JSAMPROW			row_pointer[1]; // pointer to JSAMPLE row[s]
  int				row_stride;     // physical row width in image buffer
 
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  if ((outfile = fopen("rt.jpeg", "wb")) == NULL)
    {
      my_putstr("JPEG creation : open failed\n", 2);
      return ;
    }
  jpeg_stdio_dest(&cinfo, outfile);
  cinfo.image_width  = rs->eyes->larg;           // |-- image width and height in pixels
  cinfo.image_height = rs->eyes->lng;            // |
  cinfo.input_components = 3;			 // number of color components per pixel
  cinfo.in_color_space = JCS_RGB;		 // colorspace of input image as RGB
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, JPEG_QUALITY, TRUE);
  img_creation(cinfo, row_pointer, row_stride); 
  jpeg_finish_compress(&cinfo);
  fclose(outfile);
  jpeg_destroy_compress(&cinfo);
  my_putstr("L'image a été sauvegardée sous format JPEG.\n", 1);
}
