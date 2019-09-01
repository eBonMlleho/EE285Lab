#include <fftw3.h>
#include <stdio.h>
#include <math.h>

	// ... should take off the first two rows of input
	 //use command line to give sample rate and block size.

int main(int argc, char *argv[]){
	int i;
	int sampleRate = 48000;
	int sampleSize = 0;
	for (i = 1; i < argc; i++) { 
		if (argv[i][0] == 's') {
			sampleRate = atoi(argv[i+1]);
		}
		if (argv[i][0] == 'n') {
			sampleSize = atoi(argv[i+1]);   //sampleSize == 'N' in later code
		}
	}

    fftw_complex *in, *out;
    fftw_plan p;
	
	// ...
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * sampleSize);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * sampleSize);
	p = fftw_plan_dft_1d(sampleSize, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	char trash[100];

	int index=0;
	int index1 = 0;
	double dominant_frequency1,dominant_frequency2,dominant_frequency3,dominant_frequency;
	
	double inReal, inImag;
	int k;
	double mag = 0;
	int indexPeak1 = 0;
	int indexPeak2 = 0;
	int indexPeak3 = 0;
	int j;

	
	
		fgets(trash, 100, stdin);
	fgets(trash, 100, stdin);
	fgets(trash, 100, stdin);
	fgets(trash, 100, stdin);
	 j =0;
	while(!feof(stdin) ){ 		//how to know it stopped?
		for(i=0;i<sampleSize;i++){ 		
			scanf("%lf %lf\n", &inImag, &inReal); 
		
			in[i][0] = inReal;
	   		in[i][1] = 0;
		}
		fftw_execute(p); /* repeat as needed */



		
		for(k=0;k<sampleSize/2;k++){   		//find the highest peak
			if(   sqrt(  pow(out[k-1][0],2) + pow(out[k-1][1],2) )<  sqrt(  pow(out[k][0],2) + pow(out[k][1],2) )  &&
			(	sqrt(  pow(out[k][0],2) + pow(out[k][1],2) ) > sqrt(  pow(out[k+1][0],2) + pow(out[k+1][1],2) )	) ){
				
			indexPeak1 = k;
			
			}
			

		}
//		sqrt(  pow(out[indexPeak1][0],2) + pow(out[indexPeak1][1],2) ) = 0; //assign the max peak to 0

		for(k=0;k<indexPeak1-30;k++){  	//find the second largest  index value
			
			if( sqrt(  pow(out[k-1][0],2) + pow(out[k-1][1],2) )<  sqrt(  pow(out[k][0],2) + pow(out[k][1],2) )  &&
			(	sqrt(  pow(out[k][0],2) + pow(out[k][1],2) ) > sqrt(  pow(out[k+1][0],2) + pow(out[k+1][1],2) )	) && 
			(		k!=indexPeak1		) ){
				indexPeak2 = k;
			}

		}

		for(k=0;k<indexPeak2-30;k++){  	//find the smallest peak index value 	//30 is tolerance // can be changed
			
			if( sqrt(  pow(out[k-1][0],2) + pow(out[k-1][1],2) )<  sqrt(  pow(out[k][0],2) + pow(out[k][1],2) )  &&
			(	sqrt(  pow(out[k][0],2) + pow(out[k][1],2) ) > sqrt(  pow(out[k+1][0],2) + pow(out[k+1][1],2) )	) && 
			(		k!=index		) ){
				indexPeak3 = k;
			}

		}


/*
		printf("The indexPeak3 is %d\n", indexPeak1);
		printf("The indexPeak2 is %d\n", indexPeak2);
		printf("The indexPeak1 is %d\n", indexPeak3); */
	/*	dominant_frequency1 = indexPeak3 * sampleRate / sampleSize;		
		printf("The first dominant frequency is %.2lf Hz.\n", dominant_frequency1);
		dominant_frequency2 = indexPeak2 * sampleRate / sampleSize;		
		printf("The second dominant frequency is %.2lf Hz.\n", dominant_frequency2);
		dominant_frequency3 = indexPeak1 * sampleRate / sampleSize;		
		printf("The third dominant frequency is %.2lf Hz.\n", dominant_frequency3);	
		*/


	}

	fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);

		dominant_frequency1 = indexPeak3 * sampleRate / sampleSize;			//choose the last three out of 12 lines. 
		printf("The first dominant frequency is %.2lf Hz.\n", dominant_frequency1);
		dominant_frequency2 = indexPeak2 * sampleRate / sampleSize;		
		printf("The second dominant frequency is %.2lf Hz.\n", dominant_frequency2);
		dominant_frequency3 = indexPeak1 * sampleRate / sampleSize;		
		printf("The third dominant frequency is %.2lf Hz.\n", dominant_frequency3);	


}







