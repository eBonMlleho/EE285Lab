#include <stdio.h>
#include <string.h>

#define MAXWIDTH 500
#define MAXHEIGHT 500
#define COLORS 3
#define MAXC 256

void ppmout(int w, int h, int maxc, int im[][MAXHEIGHT][COLORS], FILE * output_file);	//prototype
void ppmread(int* w, int* h, int* maxc, int im[][MAXHEIGHT][COLORS], FILE * input_file);
void blockave(int im[][MAXHEIGHT][COLORS], int w, int h, int xfrom, int yfrom, int xto, int yto, int aves[]);
void meanf(int w, int h,int d, int src[][MAXHEIGHT][COLORS], int dst[][MAXHEIGHT][COLORS]);

int image[MAXWIDTH][MAXHEIGHT][COLORS]; // Array that the input image will be stored in.
int image1[MAXWIDTH][MAXHEIGHT][COLORS]; // This array is the array that represents

void imhist(int w, int h, int src[][MAXHEIGHT][COLORS], int whichcolor, int hist[MAXC]);

void outputhist(int hist[MAXC], int totalpixels, int whichcolor);




int main(int argc, char*argv[]) {
	int imgWidth, imgHeight, numColors;
	FILE * ifp;							//create file as pointer
	FILE * ofp;
	int i;
	char is[20];						//store the string of file
	char os[20];
	for(i=0;i<argc;i++){
		if(argv[i][0] =='i'){
			strcpy(is, argv[i+1]); 		//get file name
			strcpy(os, argv[i+3]);		
		}
	}	
	ifp = fopen(is,"r");				//open file
	ofp = fopen(os,"w");
	
	
	ppmread(&imgWidth, &imgHeight, &numColors, image, ifp); //get the data into the image
	
	for(i=0;i < argc;i++){
		
		int x, y;	
		int redV, greenV, blueV;
		if(!strcmp(argv[i],"a")){ 	//argv[i] string == string "a" and run the following code
			
			redV = atoi(argv[i+1]); //change data type from string to int by using atoi
			greenV = atoi(argv[i+2]); 
			blueV = atoi(argv[i+3]);
			
			
			
			for(y=0;y<imgHeight;y++){ //approach each value in the pixel and add given value
				for(x=0;x<imgWidth;x++){ //using nested loop
						image[x][y][0] = image[x][y][0]+ redV;
						image[x][y][1] = image[x][y][1]+ greenV;
						image[x][y][2] = image[x][y][2]+ blueV;		
						if(image[x][y][0]>255){  // the maximum value of color is 255
							image[x][y][0] = 255;			//minimum is 0
						} 
						if(image[x][y][1]>255){	//make sure all in the correct range 
							image[x][y][1] = 255;			
						}
						if(image[x][y][2]>255){
							image[x][y][2] = 255;			
						}
						if(image[x][y][0]<0){
							image[x][y][0] = 0;			
						}
						if(image[x][y][1]<0){
							image[x][y][1] = 0;			
						}
						if(image[x][y][2]<0){
							image[x][y][2] = 0;			
						}
				}
			}
			
		}
		else if(argv[i][0] == 'm'){ 
		  	int meanfWidth;
			meanfWidth = atoi(argv[i+1]);		 //get value as width 
			meanf(imgWidth, imgHeight, meanfWidth, image, image1);
				for(y=0;y<imgHeight;y++){
					for(x=0;x<imgWidth;x++){
						image[x][y][0] = image1[x][y][0];  //define new image after meanf as image
						image[x][y][1] = image1[x][y][1];	//that we want to look
						image[x][y][2] = image1[x][y][2];
					}
				}
		}
	
	}
	ppmout(imgWidth, imgHeight, MAXC, image, ofp); //output the final image
	fclose(ifp);						//close file
	fclose(ofp);
	return 0;

}






void imhist(int w, int h, int src[][MAXHEIGHT][COLORS], int whichcolor, int hist[MAXC]){
	int i,j;
	int value;
	for(i=0;i<MAXC;i++){	 //count start at 0
		hist[i] = 0;		//{0,0,0,0,.......0,0}
	}
	
	for(i=0;i< w;i++){		//read value from image
		for( j = 0; j<h ; j++ ){
			value = src[i][j][whichcolor]; //record the accurate value according to each pixel
			hist[value] = hist[value]+1; 	//locate the position in array and start count
		}
	} 


}

void outputhist(int hist[MAXC], int totalpixels, int whichcolor){
	int i;	
	if (whichcolor ==0){
		printf("Red, count,	Percentage,\n");
		for(i=0;i<=255;i++){
			printf("%d, %d,	%6.2lf%%,\n", i, hist[i], hist[i]*1.0/totalpixels*100);	
		}	//							(index)  (counts)	(percentage)  
	}

	if (whichcolor ==1){
		printf("Green, count, Percentage,\n");
		for(i=0;i<=255;i++){
			printf("%d,	%d,	%6.2lf%%,\n", i, hist[i], hist[i]*1.0/totalpixels*100);	
		}	
	}

	if (whichcolor ==2){
		printf("Blue, count, Percentage,\n");
		for(i=0;i<=255;i++){
			printf("%d,	%d,	%6.2lf%%,\n", i, hist[i], hist[i]*1.0/totalpixels*100);	
		}	
		
	}
	

}


/**
 *  Reads an image from standard input and puts it into im
 */
void ppmread(int* w, int* h, int* maxc, int im[][MAXHEIGHT][COLORS], FILE * input_file) {
	char p;
	int three;
	int x, y, c;
	char commentline[100];
	fscanf(input_file, "%c%d", &p, &three);//read data from input file/
	fgets(commentline, 100, input_file); // consume end of line
	fgets(commentline,100, input_file); //Skip gimp-created comements
	fscanf(input_file, " %d %d", w, h);
	fscanf(input_file," %d", maxc);
    for (y = 0; y < *h; y++) {
		for (x = 0; x < *w; x++) {
        	for( c = 0; c < COLORS; c++) {
            	fscanf(input_file," %d ", &(im[x][y][c]));
			}
		}
	}
}

/**
 *  Takes an image im and outputs it to standard output
 */
void ppmout(int w, int h, int maxc, int im[][MAXHEIGHT][COLORS], FILE * output_file) {
	int x, y, c;
	fprintf(output_file,"P3\n");				//write data into output_file
	fprintf(output_file,"%d %d\n" , w, h);
	fprintf(output_file,"%d\n", maxc);
	for (y = 0; y < h; y++) {
		for(x = 0; x < w; x++) {
			for( c = 0; c < COLORS; c++) {
				fprintf(output_file, " %d ", im[x][y][c]);
			}
		}
	}

}

/**
 *  Takes an image a and sets every pixel equal to r, g, and b.
 */
void setval(int a[][MAXHEIGHT][COLORS], int w, int h, int r, int g, int b) {
	int x,y;
	for (x = 0; x < w; x++) {
		for (y = 0; y < h; y++) {
			a[x][y][0] = r;
			a[x][y][1] = g;
			a[x][y][2] = b;
		}
	}
}

/**
 *  Takes the average of a block of pixels
 */
void blockave(int im[][MAXHEIGHT][COLORS], int w, int h, int xfrom, int yfrom, int xto, int yto, int aves[]) {
	int x, y, c;
	int count=0;
	for (c = 0; c < COLORS; c++) aves[c]=0;
	for (x = xfrom; x <= xto; x++) {
		for (y = yfrom; y <= yto; y++) {
			if( x >= 0 && x < w && y >= 0 && y<h) {
				count++;
	  			for (c = 0; c < COLORS; c++) {
					aves[c] += im[x][y][c];	
				}		
			}
		}
	}
	for (c=0; c<COLORS;c++) {
		aves[c] /= count;
	}
}


/**
 *  Mean filters src and puts the result into dst
 *  Where d is the filter width
 */
void meanf(int w, int h,int d, int src[][MAXHEIGHT][COLORS], int dst[][MAXHEIGHT][COLORS]) {
	int x,y;
	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++) {
			blockave(src, w, h, x-d/2, y-d/2, x+d/2, y+d/2, dst[x][y]);
		}
	}
}
