/**
 * \file PngFile.cpp
 * Implante des fonctions de chargement et de sauvegarde de fichiers au format png dans et depuis des structures image.
 * 
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
#include <stdio.h>
#include <stdlib.h>

#include "PngFile.h"
#include "Png/png.h"
#include "Png/cexcept.h"

#define _CRT_SECURE_NO_WARNINGS

static png_structp png_ptr = NULL;
static png_infop info_ptr = NULL;

static void
png_cexcept_error(png_structp png_ptr,png_const_charp msg)
{
   if(png_ptr)
     {};
#ifndef PNG_NO_CONSOLE_IO
   fprintf(stderr,"libpng error: %s\n",msg);
#endif
}

/**
 * Charge un fichier png dans une structure image.
 *
 * @param file la chaine de caracteres contenant le nom du fichier.
 * @param image l'image recevant les pixels du fichier png
 * @param red l'adresse d'un octet destine a recueillir la valeur de composante rouge de la couleur de fond.
 * @param green l'adresse d'un octet destine a recueillir la valeur de composante verte de la couleur de fond.
 * @param blue l'adresse d'un octet destine a recueillir la valeur de composante bleue de la couleur de fond.
 * @return un entier booleen indiquant si la chargement a abouti ou non.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
int chargeImagePng(char *file,struct image *image,unsigned char *red,unsigned char *green,unsigned char *blue) { 
  unsigned long piWidth;
  unsigned long piHeight;
  png_byte pbSig[8];
  int iBitDepth;
  int iColorType;
  double dGamma;
  png_color_16 *pBackground;
  png_uint_32 ulChannels;
  png_uint_32 ulRowBytes;
  png_byte *pbImageData = NULL;
  static png_byte **ppbRowPointers = NULL;
  int i;
  static FILE *pfFile;
  pfFile = fopen(file,"rb");
  if ( !pfFile ) {
    return(0); }
  fread(pbSig,1,8,pfFile);
  if (!png_check_sig(pbSig,8)) {
    return(0); }
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,
    (png_error_ptr) png_cexcept_error,(png_error_ptr)NULL);
  if (!png_ptr) {
    return(0); }
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr,NULL,NULL);
    return(0); }
#if !defined(PNG_NO_STDIO)
  png_init_io(png_ptr,pfFile);
#else
  png_set_read_fn(png_ptr,(png_voidp)pfFile,png_read_data);
#endif
  png_set_sig_bytes(png_ptr,8);
  png_read_info(png_ptr,info_ptr);
  png_get_IHDR(png_ptr,info_ptr,&piWidth,&piHeight,&iBitDepth,&iColorType,NULL,NULL,NULL);
  if (iBitDepth == 16)
    png_set_strip_16(png_ptr);
  if (iColorType == PNG_COLOR_TYPE_PALETTE)
    png_set_expand(png_ptr);
  if (iBitDepth < 8)
    png_set_expand(png_ptr);
  if (png_get_valid(png_ptr,info_ptr,PNG_INFO_tRNS))
    png_set_expand(png_ptr);
  if (iColorType == PNG_COLOR_TYPE_GRAY ||
    iColorType == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png_ptr);
  if (png_get_bKGD(png_ptr,info_ptr,&pBackground)) {
    png_set_background(png_ptr,pBackground,PNG_BACKGROUND_GAMMA_FILE,1,1.0);
    *red   = (unsigned char) pBackground->red;
    *green = (unsigned char) pBackground->green;
    *blue  = (unsigned char) pBackground->blue; }
        
        // if required set gamma conversion
        if (png_get_gAMA(png_ptr,info_ptr,&dGamma))
            png_set_gamma(png_ptr,(double) 2.2,dGamma);
        
        // after the transformations have been registered update info_ptr data
        
        png_read_update_info(png_ptr,info_ptr);
        
        // get again width,height and the new bit-depth and color-type
        
        png_get_IHDR(png_ptr,info_ptr,&piWidth,&piHeight,&iBitDepth,
            &iColorType,NULL,NULL,NULL);
        
        
        // row_bytes is the width x number of channels
        
        ulRowBytes = png_get_rowbytes(png_ptr,info_ptr);
        ulChannels = png_get_channels(png_ptr,info_ptr);
                
        // now we can allocate memory to store the image
        
        if (pbImageData)
        {
            free (pbImageData);
            pbImageData = NULL;
        }
        if ((pbImageData = (png_byte *) malloc(ulRowBytes * (piHeight)
                            * sizeof(png_byte))) == NULL)
        {
            png_error(png_ptr,"Visual PNG: out of memory");
        }
        
        // and allocate memory for an array of row-pointers
        
        if ((ppbRowPointers = (png_bytepp) malloc((piHeight)
                            * sizeof(png_bytep))) == NULL)
        {
            png_error(png_ptr,"Visual PNG: out of memory");
        }
        
        // set the individual row-pointers to point at the correct offsets
        
        for (i = 0;((unsigned long) i) < (piHeight); i++)
            ppbRowPointers[i] = pbImageData + i * ulRowBytes;
        
        // now we can go ahead and just read the whole image
        
        png_read_image(png_ptr,ppbRowPointers);
        
        // read the additional chunks in the PNG file (not really needed)
        
        png_read_end(png_ptr,NULL);
        
        // and we're done
        
        free(ppbRowPointers);
        ppbRowPointers = NULL;
        
        // yepp,done

    png_destroy_read_struct(&png_ptr,&info_ptr,NULL);

    fclose (pfFile);
    allocationImage((int)piWidth,(int)piHeight,image);
    for ( i = 0 ;((unsigned long) i) < 3*piWidth*piHeight ; i++ )
      image->p[i] = pbImageData[i];
    free (pbImageData);
    return(1);
}

/**
 * Sauvegarde une structure image dans un fichier png.
 *
 * @param file la chaine de caracteres contenant le nom du fichier.
 * @param image l'image a sauvegarder.
 * @return un entier booleen indiquant si la chargement a abouti ou non.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
int sauveImagePng(char *file,struct image *image) {
    const int ciBitDepth = 8;
 //   const int iChannels = 3;
    png_uint_32 ulRowBytes;
    static png_byte **ppbRowPointers = NULL;
    int i;
    static FILE *pfFile;
    pfFile = fopen(file,"wb");

    // open the PNG output file

    if ( !pfFile )
        return(0);

    // prepare the standard PNG structures

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,NULL,
      (png_error_ptr) png_cexcept_error,(png_error_ptr)NULL);
    if (!png_ptr)
    {
        fclose(pfFile);
        return(0);
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        fclose(pfFile);
        png_destroy_write_struct(&png_ptr,(png_infopp) NULL);
        return(0);
    }

        
#if !defined(PNG_NO_STDIO)
        png_init_io(png_ptr,pfFile);
#else
        png_set_write_fn(png_ptr,(png_voidp)pfFile,png_write_data,png_flush);
#endif
        
        // we're going to write a very simple 3x8 bit RGB image
        
        png_set_IHDR(png_ptr,info_ptr,image->tx,image->ty,ciBitDepth,
            PNG_COLOR_TYPE_RGB,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,
            PNG_FILTER_TYPE_BASE);
        
        // write the file header information
        
        png_write_info(png_ptr,info_ptr);
        
        // swap the BGR pixels in the DiData structure to RGB
        
        png_set_bgr(png_ptr);
        
        // row_bytes is the width x number of channels
        
        ulRowBytes = image->tx * 3;
        
        png_byte *pDiData =(png_byte *) malloc(3*image->tx*image->ty*sizeof(png_byte));
        for ( i = 0 ; i < 3*image->tx*image->ty ; i += 3 ) {
          pDiData[i] =(png_byte) image->p[i+2];
          pDiData[i+1] =(png_byte) image->p[i+1];
          pDiData[i+2] =(png_byte) image->p[i]; }
        
        // we can allocate memory for an array of row-pointers
        
        (ppbRowPointers = (png_bytepp) malloc(image->ty * sizeof(png_bytep)));
        
        // set the individual row-pointers to point at the correct offsets
        
        for (i = 0; i < image->ty; i++)
            ppbRowPointers[i] = pDiData + i * ulRowBytes;
        
        // write out the entire image data in one call
        
        png_write_image (png_ptr,ppbRowPointers);
        
        // write the additional chunks to the PNG file (not really needed)
        
        png_write_end(png_ptr,info_ptr);
        
        // and we're done
        
        free (ppbRowPointers);
        free(pDiData);
        ppbRowPointers = NULL;
        
        // clean up after the write,and free any memory allocated
        
        png_destroy_write_struct(&png_ptr,&info_ptr);
//        png_destroy_write_struct(&png_ptr,(png_infopp) NULL);
        
        // yepp,done
    fclose (pfFile);
    
    return(1);
}

#ifdef PNG_NO_STDIO

static void
png_read_data(png_structp png_ptr,png_bytep data,png_size_t length)
{
   png_size_t check;

   /* fread() returns 0 on error,so it is OK to store this in a png_size_t
    * instead of an int,which is what fread() actually returns.
    */
   check = (png_size_t)fread(data,(png_size_t)1,length,
      (FILE *)png_ptr->io_ptr);

   if (check != length)
   {
      png_error(png_ptr,"Read Error");
   }
}

static void
png_write_data(png_structp png_ptr,png_bytep data,png_size_t length)
{
   png_uint_32 check;

   check = fwrite(data,1,length,(FILE *)(png_ptr->io_ptr));
   if (check != length)
   {
      png_error(png_ptr,"Write Error");
   }
}

static void
png_flush(png_structp png_ptr)
{
   FILE *io_ptr;
   io_ptr = (FILE *)CVT_PTR((png_ptr->io_ptr));
   if (io_ptr != NULL)
      fflush(io_ptr);
}

#endif

//-----------------
//  end of source
//-----------------
