
/*
To compile type:
gcc -o example-color example-color.c img_pro.c -lm
Note that img_pro.c and img_pro.h are updated to handle color images
*/


#include "../headers/img_pro.h"
#include "../headers/rgbgauss.h"


int main(int argc, char **argv){

/*--------->> handling command line arguments*/

if(argc!=6) {
  printf("\n Usage: example1 [Rflag] [Gflag] [Bflag] [number of Iteretions] [Image file (*.ppm)] \n");
  printf("\n [Rflag] :  Apply filter on R values or not. Takes values 1 or 0\n");
  printf("\n [Gflag] :  Apply filter on G values or not. Takes values 1 or 0\n");
  printf("\n [Bflag] :  Apply filter on B values or not. Takes values 1 or 0\n");
  printf("\n [number of Iterations] :  Apply filter [number of Iterations] times (bigger number means bigger size kernel)\n");
  printf("\n E.g.   example1 1 1 0 5 mandrill.ppm\n");
  exit(-1);
}

int Rflag = atoi(argv[1]);
int Gflag = atoi(argv[2]);
int Bflag = atoi(argv[3]);
int iter  = atoi(argv[4]);
char *ppm_file;
ppm_file = argv[5];

/*--------->>end of handling command line arguments*/

int i,j,NR,NC,NR2,NC2;
color **img;
color **imgOut;

/*---------->>> Start image manipulation example */
img=(color **)ppm_file_to_img(ppm_file,&NC,&NR);/* read img and its size from file, also allocates memory for img */

imgOut = (color **)alloc_color_img(NC,NR); /* allocate memory for imgOut*/

imgOut = (color **)rgbgauss(img, Rflag, Gflag, Bflag, NC, NR, iter); // gaussian filtering

img_to_ppm_file(imgOut,"test2.ppm",NC,NR);/*  write to file */

show_pgm_file(ppm_file);
show_pgm_file("test2.ppm");/*  show image using an external viewer */

free_color_img(img); /* free array */
free_color_img(imgOut);

}
