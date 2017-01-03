
#include "../headers/img_pro.h"

/*
*
*   @parameters input img, starting row K, bandwidth d, number of columns and rows of input img
*
*
*   @returns imgOut
*/

color **tilt_shift_rectangular(color **img, int K, int d, int NC, int NR){

    int i, j, k, m = 1, t;
    int sumR = 0, sumG = 0, sumB = 0;
    int kernel[5] = {1,4,6,4,1}; //gaussian kernel



    color **imgOut;
    imgOut = (color **)alloc_color_img(NC,NR);  //alloc memory for output image


    while(K - m*d > 0 && K + m*d < NR){

        /*-------------->>>convolution with kernel along ROWS*/
        for(i = 0; i < NR; i++){
            for(j = 0; j < NC; j++){

                //dont make any changes on the given band
                if(i > K-m*d && i < K+m*d){
                    imgOut[i][j].r = img[i][j].r;
                    imgOut[i][j].g = img[i][j].g;
                    imgOut[i][j].b = img[i][j].b;
                    continue;
                }
                for(k = -2; k <= 2; k++){
                    if(i+k > NR || i+k < 0 ){    //check for the pixel out of img
                        continue;
                    }
                    else{
                        sumR = sumR + img[i+k][j].r * kernel[k+2];
                        sumG = sumG + img[i+k][j].g * kernel[k+2];
                        sumB = sumB + img[i+k][j].b * kernel[k+2];
                    }
                }

                imgOut[i][j].r = sumR/16;

                imgOut[i][j].g = sumG/16;

                imgOut[i][j].b = sumB/16;

                sumR = 0; sumG = 0; sumB = 0;
            }


        }
        /*-------------->>>END OF convolution with kernel along rows*/



        /*-------------->>>convolution with kernel along COLUMNS*/
        for(i = 0; i < NR; i++){
            for(j = 0; j < NC; j++){

                //dont make changes on the given band
                if(i > K-m*d && i < K+m*d){
                    imgOut[i][j].r = img[i][j].r;
                    imgOut[i][j].g = img[i][j].g;
                    imgOut[i][j].b = img[i][j].b;
                    continue;
                }

                for(k = -2; k <= 2; k++){
                    if(j+k > NC || j+k < 0 ){  //check for the pixel out of img
                        continue;
                    }

                    else {
                        sumR = sumR + img[i][j+k].r * kernel[k+2];
                        sumG = sumG + img[i][j+k].g * kernel[k+2];
                        sumB = sumB + img[i][j+k].b * kernel[k+2];
                    }
                }

                imgOut[i][j].r = sumR/16;

                imgOut[i][j].g = sumG/16;

                imgOut[i][j].b = sumB/16;

                sumR = 0; sumG = 0; sumB = 0;
            }
        }
        /*-------------->>>END OF convolution with kernel along COLUMNS*/

        m++;
        img = imgOut; //this assignment required because we dont want to filter same image at each iteration
    }

    return imgOut;
}

color **tilt_shift_circular(color **img, int center_i, int center_j, int d, int NC, int NR){
    int i, j, k, m = 1, t;
    int sumR = 0, sumG = 0, sumB = 0;
    int kernel[5] = {1,4,6,4,1}; //gaussian kernel



    color **imgOut;
    imgOut = (color **)alloc_color_img(NC,NR);  //alloc memory for output image


    while(center_i - m*d > 0 && center_i + m*d < NR && center_j - m*d > 0 && center_j - m*d < NC){

        /*-------------->>>convolution with kernel along ROWS*/
        for(i = 0; i < NR; i++){
            for(j = 0; j < NC; j++){

                //dont make any changes on the given band
                if(pow(i-center_i,2) + pow(j-center_j,2) < pow(m*d, 2)){
                    imgOut[i][j].r = img[i][j].r;
                    imgOut[i][j].g = img[i][j].g;
                    imgOut[i][j].b = img[i][j].b;
                    continue;
                }
                for(k = -2; k <= 2; k++){
                    if(i+k > NR || i+k < 0 ){    //check for the pixel out of img
                        continue;
                    }
                    else{
                        sumR = sumR + img[i+k][j].r * kernel[k+2];
                        sumG = sumG + img[i+k][j].g * kernel[k+2];
                        sumB = sumB + img[i+k][j].b * kernel[k+2];
                    }
                }

                imgOut[i][j].r = sumR/16;

                imgOut[i][j].g = sumG/16;

                imgOut[i][j].b = sumB/16;

                sumR = 0; sumG = 0; sumB = 0;
            }


        }
        /*-------------->>>END OF convolution with kernel along rows*/



        /*-------------->>>convolution with kernel along COLUMNS*/
        for(i = 0; i < NR; i++){
            for(j = 0; j < NC; j++){

                //dont make changes on the given band
                if(pow(i-center_i,2) + pow(j-center_j,2) < pow(m*d, 2)){
                    imgOut[i][j].r = img[i][j].r;
                    imgOut[i][j].g = img[i][j].g;
                    imgOut[i][j].b = img[i][j].b;
                    continue;
                }

                for(k = -2; k <= 2; k++){
                    if(j+k > NC || j+k < 0 ){  //check for the pixel out of img
                        continue;
                    }

                    else {
                        sumR = sumR + img[i][j+k].r * kernel[k+2];
                        sumG = sumG + img[i][j+k].g * kernel[k+2];
                        sumB = sumB + img[i][j+k].b * kernel[k+2];
                    }
                }

                imgOut[i][j].r = sumR/16;

                imgOut[i][j].g = sumG/16;

                imgOut[i][j].b = sumB/16;

                sumR = 0; sumG = 0; sumB = 0;
            }
        }
        /*-------------->>>END OF convolution with kernel along COLUMNS*/

        m++;
        img = imgOut; //this assignment required because we dont want to filter same image at each iteration
    }

    return imgOut;
}
