// Wen Zhanghao
#include "ee285pico.h"
#include <stdio.h>
#include "/opt/picoscope/include/libps2000-2.1/ps2000.h"



//program open the oscilloscope 

int main(){
	int i;
	int b;
	long c;
	short d;
	int no_of_values=8000;
	short buffer_a[8000];
	short a; 
	short handle=-1;  // start the loop


	while(handle<=0){ 						// retuen > 0 if oscilloscope opened, so <=0 loop until it open
		handle = ps2000_open_unit();  		//ps2000_open_unit function opens a picoScope 2000 series oscilloscope
		if (handle == -1){					//return if the oscilloscope fails to open
			fprintf(stderr,"oscilloscope fails to open\n");
		}
		else if(handle == 0){				//return if no oscilloscope is found
			fprintf(stderr,"no oscilloscope is found\n");
			break;
		}
	
	}
	fprintf(stderr,"success\n");


//program selects channel ranges and coupling

	a = ps2000_set_channel(handle, 0, TRUE, FALSE, 7);
	if(a == 0){
		fprintf(stderr,"unsuccessful\n");	
	}
	else if(a !=0){
		fprintf(stderr,"Channal Successful\n");
	}


	while(kbhit()==0) {

// run block 
		d = ps2000_run_block(handle,8000,15,1,NULL);
		if (d == 0) {
			fprintf(stderr,"one of the parameters is out of range\n");
		}


//program waits for Picoscope to be ready
		while(b<=0){
			b = ps2000_ready(handle);	
			if(b==-1){
				fprintf(stderr,"oscilloscope is not attached\n");
			}
		
		}
// get value
		c = ps2000_get_values(handle, buffer_a, NULL, NULL, NULL, NULL, no_of_values);
		if(c==0){
			printf("out of range\n");
		}
		for(i=0;i<8000;i++){
			//fprintf(stderr,"%lf %lf\n", (double)i, buffer_a[i]*1.0); 
			printf("%lf %lf\n", (double)i, buffer_a[i]*1.0); 
		}
	}






//ps2000 stop oscilloscope
	ps2000_stop(handle);

}
