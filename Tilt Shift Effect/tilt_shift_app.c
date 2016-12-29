
/*
To compile type:
gcc -o example-color example-color.c img_pro.c -lm
Note that img_pro.c and img_pro.h are updated to handle color images
*/


#include "../headers/img_pro.h"
#include "../headers/tilt_shift.h"


int main(int argc, char **argv){

/*--------->> handling command line arguments*/

if(argc!=4) {
  printf("\n Usage: example1 [Rflag] [Gflag] [Bflag] [number of Iteretions] [Image file (*.ppm)] \n");
  printf("\n [K] :  Apply filter on R values or not. Takes values 1 or 0\n");
  printf("\n [d] :  Apply filter [number of Iterations] times (bigger number means bigger size kernel)\n");
  printf("\n E.g.   example1 200 20 mandrill.ppm\n");
  exit(-1);
}

int K = atoi(argv[1]);

int d = atoi(argv[2]);

char *ppm_file;
ppm_file = argv[3];

/*--------->>end of handling command line arguments*/

int i,j,NR,NC,NR2,NC2;
color **img;
color **imgOut;


img=(color **)ppm_file_to_img(ppm_file,&NC,&NR);/* read img and its size from file, also allocates memory for img */

imgOut = (color **)alloc_color_img(NC,NR); /* allocate memory for imgOut*/

imgOut = (color **)tilt_shift(img, K, d, NC, NR); // gaussian filtering

img_to_ppm_file(imgOut,"test2.ppm",NC,NR);/*  write to file */

show_pgm_file(ppm_file);
show_pgm_file("test2.ppm");/*  show image using an external viewer */

free_color_img(img); /* free array */
free_color_img(imgOut);

}
