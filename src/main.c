/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Wed Aug 14 2002
    copyright            : (C) 2002 by Christophe Combelles
    email                : ccomb@free.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <stdio.h>
#include "png.h"
int syntax() {
  printf("\nsyntax : neurec filename.png\n");
  return 1;
}

#define PNG_BYTES_TO_CHECK 4
int open_if_png(char *file_name, FILE **ppf)
{
  char buf[PNG_BYTES_TO_CHECK];

  /* Open the prospective PNG file. */
  if ((*ppf = fopen(file_name, "rb")) == NULL) {
    return 0;
  }
  /* Read in some of the signature bytes */
  if (fread(buf, 1, PNG_BYTES_TO_CHECK, *ppf) != PNG_BYTES_TO_CHECK) {
    close(*ppf);
    return 0;
  }
  /* Compare the first PNG_BYTES_TO_CHECK bytes of the signature.
  *       Return nonzero (true) if they match */
  return(!png_sig_cmp(buf, (png_size_t)0, PNG_BYTES_TO_CHECK));
}

int main(int argn, char *argv[]) {
  FILE *pimage;
  int is_readable_png;
  png_structp png_ptr;
  png_infop info_ptr;
  png_uint_32 width, height;
  png_voidp user_error_ptr, user_error_fn, user_warning_fn;
  int bit_depth, color_type, interlace_type;

  if (argn!=2) {
    syntax();
    exit(1);
  }
  is_readable_png = open_if_png(argv[1], &pimage);
  if (!is_readable_png) {
    printf("incorrect file\n");
    exit(1);
  }
  printf("correct file\n");
  /* read the png file */
  rewind(pimage);
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, user_error_ptr, user_error_fn, user_warning_fn);
  if (png_ptr == NULL) {
    fclose(pimage);
    return 1;
  }
  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL) {
    fclose(pimage);
    png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
    return 1;
  }
  /* mandatory error handling with libpng */
  if (setjmp(png_jmpbuf(png_ptr)))
  {
    /* Free all of the memory associated with the png_ptr and info_ptr */
    png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
    fclose(pimage);
    /* If we get here, we had a problem reading the file */
    return 1;
  }
  /* init io for libpng */
  png_init_io(png_ptr, pimage); 
  /* read the whole image */
  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 || PNG_TRANSFORM_STRIP_ALPHA, png_voidp_NULL);
  printf("file read");     

  /* now we will try to display the image */
  
  /*...*/

  /* now we create a thread to transform and display the image */

  /* go into a loop to get the position of the mouse pointer,
   * and give it to the thread, so that it can display it according to the position */

  
  
  fclose(pimage);

    
  
}
