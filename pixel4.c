//To  *scale*  a Bmp image.... by providing path of input image,output image,  and the new width and height
//To find the  *RGB values*  of all the pixels of the scaled image and output the values to a text file in given path

#include "gd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int main (int argc, char *argv[]) 
 {
	FILE *fp;
	gdImagePtr in, out;
	int w, h;

	/* Help */
	if (argc<=4) {
		printf("%s  input.bmp  output.bmp  width  height\n", argv[0]);
		return 1;
	}

	/* Size */
	w = atoi(argv[3]);
	h = atoi(argv[4]);
	if (w<=0 || h<=0) {
		fprintf(stderr, "Bad size %dx%d\n", h, w);
		return 2;
	}

	/* Input */
	fp = fopen(argv[1], "rb");
	if (!fp) {
        fprintf(stderr, "Can't read image %s\n", argv[1]);
		return 3;
	}
	in = gdImageCreateFromBmp(fp);
	fclose(fp);
	if (!in) {
		fprintf(stderr, "Can't create image from %s\n", argv[1]);
		return 4;
	}

	/* Resize */
	gdImageSetInterpolationMethod(in, GD_BILINEAR_FIXED);
	out = gdImageScale(in, w, h);
	if (!out) {
		fprintf(stderr, "gdImageScale fails\n");
		return 5;
	}

	/* Output */
	fp = fopen(argv[2], "wb");
	if (!fp) {
		fprintf(stderr, "Can't save image %s\n", argv[2]);
		return 6;
	}
	gdImageBmp(out, fp, 90);

        fclose(fp);


//RGB calculation
int i;
char *filename;
FILE *streamIn;

streamIn = fopen(argv[2], "r");

int byte;
 unsigned char header[54];
 int count = 0;
 for(i=0;i<54;i++) 
       header[i] = getc(streamIn);  
 int width = *(int*)&header[18]; 
 int height = *(int*)&header[22];
int image[height*width][3];

FILE *fptr;
   fptr = fopen("/home/user/Desktop/RGB4.txt","w");
if (fptr == NULL) 
    { 
        printf("Could not open file"); 
        return 0; 
    } 
 for(i=0;i<(height*width);i++){    
    image[i][2] = getc(fp);  
    image[i][1] = getc(fp);  
    image[i][0] = getc(fp);  
   fprintf(fptr,"pixel %d : [%d,%d,%d]\n",i+1,image[i][0],image[i][1],image[i][2]);
 }
fclose(fptr);
fclose(streamIn);

	/* Cleanups */
	gdImageDestroy(in);
	gdImageDestroy(out);

	return 0;
}

//commands:-
//          gcc pixel4.c -lgd
//          ./a.out /home/user/Desktop/krishna/w3c.bmp /home/user/Desktop/w3c1.bmp 100 100

//input image:- /home/user/Desktop/krishna/w3c.bmp (72*48)
//output image:- /home/user/Desktop/w3c1.bmp
//scaled width*height :- 100 *100 (10000 pixels)
//output file:-  /home/user/Desktop/RGB4.txt

