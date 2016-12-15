#include "../headers/img_pro.h"

/*
*   rgbgauss filters an image for a given RGBflag that
*   combinations of R, G and B whether they are 0 or 1,
*   means that for example 101 is filters R and B values.
*
*   @parameters input img, RGBflag, number of columns and rows of input img
*
*
*   @returns imgOut
*/

color **rgbgauss(color **img, int R, int G, int B, int NC, int NR, int n_iter){

    int i, j, k, m = 3, t;
    int sumR = 0, sumG = 0, sumB = 0;
    int kernel[3] = {1,2,1}; //gaussian kernel. I think It is not looking nice here because it is hard coded
                             


    color **imgOut;
    imgOut = (color **)alloc_color_img(NC,NR);  //alloc memory for output image

    /*-------------->>>convolution with kernel along ROWS*/
    for(t = 0; t < n_iter; t++){
        for(i = 0; i < NR; i++){
            for(j = 0; j < NC; j++){
                for(k = -1; k <= 1; k++){
                    if(i+k > NR || i+k < 0 ){
                        continue;
                    }
                    else{

                        sumR = sumR + img[i+k][j].r * kernel[k+1];
                        sumG = sumG + img[i+k][j].g * kernel[k+1];
                        sumB = sumB + img[i+k][j].b * kernel[k+1];
                    }

                }
                if(!R) img[i][j].r = img[i][j].r;    //chek user whether or not filter the R values
                else imgOut[i][j].r = sumR/4;

                if(!G) img[i][j].g = img[i][j].g;    //chek user whether or not filter the G values
                else imgOut[i][j].g = sumG/4;

                if(!B) img[i][j].b = img[i][j].b;    //chek user whether or not filter the B values
                else imgOut[i][j].b = sumB/4;

                sumR = 0; sumG = 0; sumB = 0;
            }
        }
        /*-------------->>>END OF convolution with kernel along rows*/



        /*-------------->>>convolution with kernel along COLUMNS*/
        for(i = 0; i < NR; i++){
            for(j = 0; j < NC; j++){
                for(k = -1; k <= 1; k++){
                    if(j+k > NC || j+k < 0 ){
                        continue;
                    }
                    else {
                        sumR = sumR + img[i][j+k].r * kernel[k+1];
                        sumG = sumG + img[i][j+k].g * kernel[k+1];
                        sumB = sumB + img[i][j+k].b * kernel[k+1];
                    }
                }
                if(!R) img[i][j].r = img[i][j].r;    //chek user whether or not filter the R values
                else imgOut[i][j].r = sumR/4;

                if(!G) img[i][j].g = img[i][j].g;    //chek user whether or not filter the G values
                else imgOut[i][j].g = sumG/4;

                if(!B) img[i][j].b = img[i][j].b;    //chek user whether or not filter the B values
                else imgOut[i][j].b = sumB/4;

                sumR = 0; sumG = 0; sumB = 0;
            }
        }
        /*-------------->>>END OF convolution with kernel along COLUMNS*/


        img = imgOut; //this assignment required because we dont want to filter same image at each iteration

        // !!! maybe a temp image can be used because we dont want to change real image to use for another processes
        // but in this app it is not problem. we dont need real img once more
    }

    return imgOut;
}
