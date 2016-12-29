#include "../headers/img_pro.h"


color **edge_color(color **img, int Threshold, float Intensity, float Saturation, int NC, int NR){
    unsigned char **mag;
    mag=alloc_img(NC,NR);
    color **out_img;
    out_img=(color **)alloc_color_img(NC,NR);								// allocate memory for edge magnitudes
    int i,j,max=0,min=2000;
    double theta, pi=3.1415,Rx,Ry,Gx,Gy,Bx,By,gxx,gyy,gxy;
    for(i=0;i<NR;i++)
    	for(j=0;j<NC;j++)
    	{
    		if((i==0)||(j==0)||(i==NR-1)||(j==NC-1))	// skip operations for border bits
    		{
    			mag[i][j]=0;
    		}
    		else	// find edge magnitudes by using vector approach (Sobel operator is used to compute gradients) and apply threshold
    		{
    			Rx=(img[i-1][j+1].r+2*img[i][j+1].r+img[i+1][j+1].r-img[i-1][j-1].r-2*img[i][j-1].r-img[i+1][j-1].r);
    			Ry=(img[i-1][j+1].r+2*img[i-1][j].r+img[i-1][j-1].r-img[i+1][j+1].r-2*img[i+1][j].r-img[i+1][j-1].r);
    			Gx=(img[i-1][j+1].g+2*img[i][j+1].g+img[i+1][j+1].g-img[i-1][j-1].g-2*img[i][j-1].g-img[i+1][j-1].g);
    			Gy=(img[i-1][j+1].g+2*img[i-1][j].g+img[i-1][j-1].g-img[i+1][j+1].g-2*img[i+1][j].g-img[i+1][j-1].g);
    			Bx=(img[i-1][j+1].b+2*img[i][j+1].b+img[i+1][j+1].b-img[i-1][j-1].b-2*img[i][j-1].b-img[i+1][j-1].b);
    			By=(img[i-1][j+1].b+2*img[i-1][j].b+img[i-1][j-1].b-img[i+1][j+1].b-2*img[i+1][j].b-img[i+1][j-1].b);
    			gxx=Rx*Rx+Gx*Gx+Bx*Bx;
    			gyy=Ry*Ry+Gy*Gy+By*By;
    			gxy=Rx*Ry+Gx*Gy+Bx*By;
    			theta=0.5*atan2(2*gxy,(gxx-gyy));
    			mag[i][j]=(floor(sqrt(0.5*((gxx+gyy)-(gxx-gyy)*cos(2*theta)+2*gxy*sin(2*theta)))+0.5))/8;
    			if(mag[i][j]<Threshold)
    				mag[i][j]=0;
    		}
    	}


    for(i=0;i<NR;i++) 				// find max and min(other than zero) from the magnitude array
    	for(j=0;j<NC;j++)
    	{
    		if(mag[i][j]>max)
    			max=mag[i][j];
    		if(mag[i][j]<min)
    			if(mag[i][j]!=0)
    				min=mag[i][j];
    	}

    out_img=(color **)alloc_color_img(NC,NR);	// allocate memory for output image

    // using edge magnitudes to adjust hue of the output image starts
    for(i=0;i<NR;i++)
    	for(j=0;j<NC;j++)
    	{
    		if(mag[i][j]==0)			// the values under the "Threshold" will be shown as white
    		{
    			out_img[i][j].r=255;
    			out_img[i][j].g=255;
    			out_img[i][j].b=255;
    		}
    		else						// the values over the "Threshold" will be processed to adjust hue within the range 0-240
    		{							// the strongest edges are going to be red(0), the weakest edges are going to be blue(240)
    			mag[i][j]=mag[i][j]-min;
    			mag[i][j]=239*mag[i][j]/(max-min);	// all values within the range "min-max" mapped through "0-240"
    			mag[i][j]=239-mag[i][j];			// the values are reverted as we want to show strongest edge on red
    			// transformation from HSI space to RGB space starts
    			if(mag[i][j]<120)
    			{
    				out_img[i][j].r=255*(Intensity*(1+((Saturation*cos(mag[i][j]*pi/180))/cos((pi/3)-mag[i][j]*pi/180))));
    				out_img[i][j].b=255*(Intensity*(1-Saturation));
    				out_img[i][j].g=255*3*Intensity-(out_img[i][j].r+out_img[i][j].b);
    			}
    			else
    			{
    				mag[i][j]=mag[i][j]-120;
    				out_img[i][j].r=255*(Intensity*(1-Saturation));
    				out_img[i][j].g=255*(Intensity*(1+((Saturation*cos(mag[i][j]*pi/180))/cos((pi/3)-mag[i][j]*pi/180))));
    				out_img[i][j].b=255*3*Intensity-(out_img[i][j].r+out_img[i][j].g);
    			}
    			// transformation from HSI space to RGB space ends
    		}
    	}
    // using edge magnitudes to adjust hue of the output image ends
    return out_img;
}
