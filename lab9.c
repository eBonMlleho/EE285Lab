#include "ee285pico.h"
#include<stdio.h>

//#define PS2000_CHANNEL_A 0

//block size = 8000 and sample rate = 6000

int main() {
	int rtn;
	int set;
	int i=0;

	//open unit
	short h;
	
	//set channel
	short handle;
	short channel=0;
	short enabled=1;
	short dc=1;
	short range=6;

	//get timebase
	//short timebase=15.0247; //<-that is questionable. the 6000 is only used in the sample rate calculation where f_s=maxsamplingrate/2^timebase
	short timebase=15; 
	long no_of_samples=8000; //this is block size
	int32_t *time_interval; //don't need to feed anything
	short *time_units; //don't need to feed anything
	short oversample=1; 
	int32_t *max_samples;//dont need to feed anything

	//run block
//	int32_t *time_indisposed_ms;
	int32_t time_indisposed_ms = 1;

	//get times and values
	int32_t *times;
	short buffer_a[8000];
	int16_t *buffer_b;//not used
	int16_t *buffer_c;//not used
	int16_t *buffer_d;//not used
	//int16_t *overflow;
	int16_t overflow = 1;
	long no_of_values = no_of_samples;
	int32_t timess[8000];

	h = ps2000_open_unit();
	if (h>0) {handle = h;}
    else {
		fprintf(stderr,"failed to get a handle\n");
		return 0;
	}
	
	//rtn = ps2000_set_channel(handle,PS2000_CHANNEL_A,TRUE,FALSE,PS2000_2V);
	rtn = ps2000_set_channel(handle,0,TRUE,TRUE,7);
	if (rtn == 0) {
		fprintf(stderr,"could not set channel\n");
		return 0;
	}
/*
	rtn = ps2000_get_timebase (handle, timebase, no_of_samples, time_interval, time_units, oversample, max_samples);
	if (rtn == 0) {
		fprintf(stderr,"error\n");
		return 0;
		}
*/
	
	i=0;
	while(kbhit()==0) {

		rtn = ps2000_run_block(handle,no_of_samples,timebase,oversample,NULL);
		if (rtn == 0) {
			fprintf(stderr,"one of the parameters is out of range\n");
			return 0;
		}

		set=0;
		while (set ==0) {
			set = ps2000_ready (handle);
			if (set<0){
				fprintf(stderr,"error: oscilloscope is not attatched");
				return 0;
			}
		}


		//rtn = ps2000_get_values(handle, buffer_a, buffer_b, buffer_c, buffer_d, &overflow, no_of_values);
		rtn = ps2000_get_times_and_values(handle, timess, buffer_a, NULL,NULL,NULL,NULL,4, no_of_values);

		if (rtn == 0) {
			fprintf(stderr, "(%d) one or more of the parameters is out of range or time unit overflow\n", overflow);
			return 0;
		}

		for(i=0;i<8000;i++){
			printf("%lf %lf", (double) i, buffer_a[i] * 1.0); //need new line?
		}
	}

	ps2000_stop (handle);

return 0;
}


