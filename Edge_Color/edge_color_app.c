
/*
To compile type:
gcc -o example-color example-color.c img_pro.c -lm
Note that img_pro.c and img_pro.h are updated to handle color images
*/


#include "../headers/img_pro.h"
#include "../headers/edge_color.h"


int main(int argc, char **argv){

/*--------->> handling command line arguments*/

if(argc!=5) {
  printf("\n Usage: example1 [Threshhold] [Intensity] [Saturation] [Image file (*.ppm)] \n");
  printf("\n E.g.   example1 10 1 1 mandrill.ppm\n");
  exit(-1);
}

int Threshold = atoi(argv[1]);
int Intensity = atoi(argv[2]);
int Saturation = atoi(argv[3]);
char *ppm_file;
ppm_file = argv[4];

/*--------->>end of handling command line arguments*/

int i,j,NR,NC,NR2,NC2;
color **img;
color **imgOut;

/*---------->>> Start image manipulation example */
img=(color **)ppm_file_to_img(ppm_file,&NC,&NR);/* read img and its size from file, also allocates memory for img */

imgOut = (color **)alloc_color_img(NC,NR); /* allocate memory for imgOut*/

imgOut = (color **)edge_color(img, Threshold, Intensity, Saturation, NC, NR); // color edge detection

img_to_ppm_file(imgOut,"test2.ppm",NC,NR);/*  write to file */

show_pgm_file(ppm_file);
show_pgm_file("test2.ppm");/*  show image using an external viewer */

free_color_img(img); /* free array */
free_color_img(imgOut);

}
