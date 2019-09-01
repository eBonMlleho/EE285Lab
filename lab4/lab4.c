#include <stdio.h>
#include <math.h>	
#include <string.h>
#define TOLERANCE1 0.35
#define TOLERANCE2 0.2
#define TOLERANCE3 0.88
#define G 9.81
	int main(){
		int time = 0;
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		int i = 0;
		double mag = 1.0;		//define the value to start the loop
		int count = 0;
		int t1=0; int t2 = 0;
			printf("I'm waiting");			
			while(mag<1+TOLERANCE1 && mag>1-TOLERANCE2){// the value choose based on another c.file for 
												//the  first drop and second drop
				scanf("%d , %lf , %lf , %lf,\n", &time, &x, &y, &z);
				mag = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
				count = count +1;
				if(count == 10){ // one period correpond to 10 input lines
					printf(".");
					count = 0; //restart counting from 0
					}
			}
			t1 = time;
			
		
		printf("\n	Help me! I'm falling");
			mag = 0.1;
			count = 0;
			while(mag<TOLERANCE3&&mag>=0.0){ //mag should smaller than the number that bigger than 0.8745
				scanf("%d , %lf , %lf , %lf,\n", &time, &x, &y, &z);
				mag = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
				count = count +1;
				if(count == 5){
					printf("!");
					count = 0;
				}
			}
		t2 = time;
			
		double h; double t;
		t = (t2-t1)/1000.0;		//compute the dalta T, and change unit
		h = 1.0/2.0*G*pow(t,2);		//compute the distance
		printf("\n		Ouch! I fell %.3lf meters in %.3lf seconds", h, t);

}
