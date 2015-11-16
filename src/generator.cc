#include "generator.hh"

error_code generate_cont(data** vector, pos_int size, int start){

	*vector = (data*)malloc(size*sizeof(data));
	
	for(pos_int i=0; i<size; i++){

		(*vector)[i]=start+i;
		
	}
	return 1;
}	


error_code generate_const(data** vector, pos_int size, int constant){

	*vector = (data*)malloc(size*sizeof(data));
	
	for(pos_int i=0; i<size; i++){

		(*vector)[i]=constant;
		
	}
	return 1;
}	

error_code generate_rand(data** vector, pos_int size){
	srand(time(NULL));
	*vector = (data*)malloc(size*sizeof(data));
	
	for(pos_int i=0; i<size; i++){

		(*vector)[i]=rand()%size;
		
	}
	return 1;
}

error_code generate_normal(data** vector, pos_int size, float mean, float variance){

	*vector = (data*)malloc(size*sizeof(data));
	
	for(pos_int i=0; i<size; i++){

		(*vector)[i]= (1/sqrt(variance*2*M_PI))*exp(-1*pow(i-mean, 2)/(2*variance));

	}
	return 1;
}	

error_code generate_exponential(data** vector, pos_int size, float lambda){

	*vector = (data*)malloc(size*sizeof(data));
	
	for(pos_int i=0; i<size; i++){

		(*vector)[i]= lambda*exp(-1*lambda*i);

	}
	return 1;
}

error_code generate_bernoulli(data** vector, pos_int size, float p){

	*vector = (data*)malloc(size*sizeof(data));
	
	for(pos_int i=0; i<size; i++){

		(*vector)[i]= pow(p,i)*pow(1-p,1-i);

	}
	return 1;
}		