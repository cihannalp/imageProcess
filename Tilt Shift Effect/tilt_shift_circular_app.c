
/*
To compile type:
gcc -o example-color example-color.c img_pro.c -lm
Note that img_pro.c and img_pro.h are updated to handle color images
*/


#include "../headers/img_pro.h"
#include "../headers/tilt_shift.h"


int main(int argc, char **argv){

/*--------->> handling command line arguments*/

if(argc!=5) {
  printf("\n Usage: example1 [center_i] [center_j] [d] [Image file (*.ppm)] \n");
  printf("\n [center_i] :  Row center point \n");
  printf("\n [center_j] :  Column center point)\n");
  printf("\n [d] :  r of circle)\n");
  printf("\n E.g.   example1 100 100 50 mandrill.ppm\n");
  exit(-1);
}

int center_i = atoi(argv[1]);

int center_j = atoi(argv[2]);

int d = atoi(argv[3]);

char *ppm_file;
ppm_file = argv[4];

/*--------->>end of handling command line arguments*/

int i,j,NR,NC,NR2,NC2;
color **img;
color **imgOut;


img=(color **)ppm_file_to_img(ppm_file,&NC,&NR);/* read img and its size from file, also allocates memory for img */

imgOut = (color **)alloc_color_img(NC,NR); /* allocate memory for imgOut*/

imgOut = (color **)tilt_shift_circular(img, center_i, center_j, d, NC, NR); // gaussian filtering

img_to_ppm_file(imgOut,"circular_result.ppm",NC,NR);/*  write to file */

show_pgm_file(ppm_file);
show_pgm_file("circular_result.ppm");/*  show image using an external viewer */

free_color_img(img); /* free array */
free_color_img(imgOut);

}
