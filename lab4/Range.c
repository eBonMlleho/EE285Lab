#include <stdio.h>
#include <math.h>	
#include <string.h>

	int main(){
		int time = 0;
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		double storeMax = 0.2;  //shoule be changed =1 if waiting 
		double storeMin = 0.2; //should be changed =1 if waiting		
		double mag=0;
		

		time = 0;					//start the loop // value is suit for drop
		while(time<____){
			scanf("%d , %lf , %lf , %lf,\n", &time, &x, &y, &z);
			mag = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
			if(storeMax<mag){
				storeMax = mag;
			}
			if(storeMin>mag){
				storeMin = mag;			
			}
			
		}				
			printf("Max: %lf Min:%lf", storeMax, storeMin);
	}

		//
