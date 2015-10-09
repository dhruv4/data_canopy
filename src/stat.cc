#include "canopy.hh"

float calculateCorelation(column* x, column* y){
	assert(x->size == y->size);
	pos_int sumx=0;
	pos_int sumy=0;
	pos_int sumx2=0;
	pos_int sumy2=0;
	pos_int sumxy=0;

	for(pos_int i=0; i<x->size; ++i){
		sumx+=x->vector[i];
		sumy+=y->vector[i];
		sumx2+=pow(x->vector[i],2);
		sumy2+=pow(y->vector[i],2);
		sumxy+=x->vector[i]*y->vector[i];
	}

	float num = (x->size*sumxy)-(sumx*sumy)*1.0;
	float den_1 = sqrt((x->size*sumx2)-pow(sumx,2));
	float den_2 = sqrt((x->size*sumy2)-pow(sumy,2));
	
	cout<<sumxy<<endl;
	cout<<sumx<<endl;
	cout<<sumy<<endl;

	cout<<num<<endl;
	cout<<den_1<<endl;
	cout<<den_2<<endl;
	
	float cor = num/(den_2*den_1);
	cout<<cor<<endl;
	return cor;
}


float calculateCorelation(data* x, pos_int size_x, data* y, pos_int size_y){
	assert(size_x == size_y);
	pos_int sumx=0;
	pos_int sumy=0;
	pos_int sumx2=0;
	pos_int sumy2=0;
	pos_int sumxy=0;

	for(pos_int i=0; i<size_x; ++i){
		sumx+=x[i];
		sumy+=y[i];
		sumx2+=pow(x[i],2);
		sumy2+=pow(y[i],2);
		sumxy+=x[i]*y[i];
	}

	float num = (size_x*sumxy)-(sumx*sumy)*1.0;
	float den_1 = sqrt((size_x*sumx2)-pow(sumx,2));
	float den_2 = sqrt((size_x*sumy2)-pow(sumy,2));	
	float cor = num/(den_2*den_1);

	return cor;
}

float calculateMean(data* x, pos_int size_x){

	int sum = 0;
	for(pos_int i=0; i<size_x; ++i){
		sum+=x[i];
	}
	return sum*1.0/size_x*1.0;
}

float calculateVariance(data* x, pos_int size_x,float mean){

	int sum = 0;
	for(pos_int i=0; i<size_x; ++i){
		sum+=pow(mean-(x[i]*1.0),2);
	}
	return sum*1.0/size_x*1.0;
}

float calculateMultiCorrelation(pos_int node_id, int chunk_number, DataCanopy* dc){

	for(pos_int j = 0 ;j < dc->md->num_col; ++j){
		
		/*Check if the particular column is of relevance to the ID*/
		
		if(( (node_id>>j) &1) == 1){
			
			/*Check what other columns are in the ID, which should be paired with this*/

			for(pos_int i = j+1; j < dc->md->num_col; ++j){

				if(( (node_id>>i) &1) == 1){
					dc->GetNodeValue(dc->GetAddress(pow(2,i)+pow(2,j),chunk_number));

				}
			}			
		}
	}
	return 0;




}



















