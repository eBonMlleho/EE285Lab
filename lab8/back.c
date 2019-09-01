#include <fftw3.h>
#include <stdio.h>
#include <math.h>

	// ... should take off the first two rows of input
	 //use command line to give sample rate and block size.

int main(int argc, char *argv[]){		//get the sampleSize and sampleRate
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

    fftw_complex *in, *out;			//initial two pointer type fftw
    fftw_plan p;
	
	// ...
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * sampleSize);	//alloc memory for them
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * sampleSize);
	p = fftw_plan_dft_1d(sampleSize, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

	

	char trash[100];

	int index=0;
	double dominant_frequency;
	double inReal, inImag;
	int k;
	double mag = 0;
	
	fgets(trash, 100, stdin);		//gets the first two lines
	fgets(trash, 100, stdin);

	while(!feof(stdin) ){ 		//do the loop until reach the end of standard input
		for(i=0;i<sampleSize;i++){ 		
			scanf("%lf %lf\n", &inImag, &inReal); 
		
			in[i][0] = inReal;  //set all the imaginary part to 0, and magnitude to real part
	   		in[i][1] = 0;
		}
			

		fftw_execute(p); /* repeat as needed */  //transfer from in, to complex number out
		for(k=0;k<sampleSize/2;k++){		//find the max value of mag
			
			if(mag < sqrt(  pow(out[k][0],2) + pow(out[k][1],2) ) ){
				mag = sqrt(  pow(out[k][0],2) + pow(out[k][1],2) );
				index = k;		// and get value of index
			}
		}
		dominant_frequency = index * sampleRate / sampleSize;		//compute the dominant frequency
		printf("Mag: %lf The dominant frequency at index %d is %.2lf Hz.\n",mag ,index, dominant_frequency);	
	


	}

	fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
}







