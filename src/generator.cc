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