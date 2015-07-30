#include "canopy.hh"

/**
*	START--Temporary functions
*/

pos_int DataCanopy::GetNodeValue(pos_int add){
	
#ifndef LOCKFREE
	return nodes.find(add)->second->statistic->num;
#else
	concurrent_map::accessor result;
	nodes.find(result,add);
	return result->second->statistic->num;
#endif	

}

/**
*	END--Temporary functions
*/


///////////////////////////////

pos_int scan(data* d, pos_int s){
	int x = 0;
	for (pos_int i = 0; i < s; ++i)
	{
		x+=d[i];
	}
	return x/s;
}

DataCanopy::DataCanopy(mdata* m){
	md=m;
	float log_nc = log2(md->num_chun);
	log_num_chun = ceil(log_nc);
	is_level_one_built=false;
	is_level_two_built=false;

}

pos_int DataCanopy::GetAddress(pos_int node, pos_int chunk){
	return node<<(log_num_chun)|chunk;
}

bool DataCanopy::IsLevelOne(pos_int x){
 	return (__builtin_popcount(x)==1);
}

bool DataCanopy::IsLevelTwo(pos_int x){
	return (__builtin_popcount(x)==2);
}

pos_int DataCanopy::ProbeCanopy(){
	
	/*pos_int n=0;
	pos_int canopy_size = pow(2,(md->num_col));

		for (pos_int i = 1; i < canopy_size ; ++i){
			for (pos_int j = 0; j < md->num_chun ; ++j){
				
				unordered_map<pos_int,node*>::const_iterator got = nodes.find(GetAddress(i,j));
				cout<<got->second->statistic->num<<endl;
				if(got==nodes.end())
					continue;
				n++;
			}

		}
	assert(n==nodes.size());
	return n;	*/
	return 0;

}



error_code DataCanopy::BuildLevelOne(pos_int start_chunk, pos_int end_chunk){
 

	int num = 0; 

	for (pos_int i = 0; i<md->num_col; ++i){
		for (pos_int k = start_chunk; k < end_chunk; ++k){
#ifdef PRINT_FOR_DEMO_INTERACT
			cout<<"level: 1, ";
			cout<<"chunk: "<<k<<", ";
			num++;
#endif
			/*Create a new node. For level one the identifier is 2^i*/
			
			node* nd = new node();
			nd->statistic = new stat();
			nd->identifier = pow(2,i);
			
			/***/

			/*Calculate and store statistics for each of the nodes based on the 
			data it accesses.*/

			nd->statistic->mean=CalculateMean(md->chunk_list[k].vectors[i],md->chunk_list[k].size);
			nd->statistic->variance=CalculateVariance(md->chunk_list[k].vectors[i],md->chunk_list[k].size,nd->statistic->mean);
			nd->statistic->standard_deviation=sqrt(nd->statistic->variance);
#ifdef PRINT_FOR_DEMO_INTERACT
			cout<<"stat: ["<<nd->statistic->mean<<","<<nd->statistic->variance<<","<<nd->statistic->standard_deviation<<"]";
			cout<<" childs: ["<<i<<"]"<<endl;
#endif
			/***/

#ifdef INSERT	
			
			/*Insert the node in the data canopy*/

			
			InsertNode(GetAddress(pow(2,i),k),nd);
			
			/***/
#endif

		}
	}

	is_level_one_built=true;

#ifdef INSERT
	//cout<<GetCanopySize()<<" "<<md->num_col*md->num_chun<<endl;
	//assert(GetCanopySize()==md->num_col*md->num_chun);

#endif

	return 1;

}

error_code DataCanopy::BuildLevelTwo(pos_int start_chunk, pos_int end_chunk){

	
	int num = 0; 

	for (pos_int i = 0; i<md->num_col; ++i){
		for (pos_int j = i+1; j<md->num_col; ++j){

			for (pos_int k = start_chunk; k < end_chunk; ++k){
				
				/*Create a new node. For level two the identifier is 2^i + 2^j, k*/

				node* nd = new node();
				nd->statistic = new stat();
				pos_int address = GetAddress(pow(2,i)+pow(2,j),k);
				nd->identifier = address;

				/***/
			
				num++;
			
				/*Calculate the correlation and store the value*/

				nd->statistic->correlation=CalculateCorrelation(md->chunk_list[k].vectors[i],md->chunk_list[k].size,md->chunk_list[k].vectors[j],md->chunk_list[k].size);
				
				/***/
#ifdef INSERT	

				InsertNode(address,nd);
#endif
			}
		}
	}
	is_level_two_built=true;

#ifdef INSERT
	//assert(GetCanopySize()==(md->num_col + (md->num_col*(md->num_col-1)/2)) * md->num_chun);
#endif

	return 1;


}


error_code DataCanopy::BuildLevelOneTwo(pos_int start_chunk, pos_int end_chunk){

	int num = 0; 
	bool is_level_one_Calculated;
	
	for (pos_int i = 0; i<md->num_col; ++i){
		is_level_one_Calculated = false;

		for (pos_int j = i+1; j<md->num_col+1; ++j){
			for (pos_int k = start_chunk; k < end_chunk; ++k){
			
			
				if (is_level_one_Calculated == false){

					/*Create a new node. For level one the identifier is 2^i*/
					
					node* nd = new node();
					nd->statistic = new stat();
					pos_int address = GetAddress(pow(2,i),k);
					nd->identifier = address;
					
					//cout<<pow(2,i)<<endl;
					/***/

					nd->statistic->mean=CalculateMean(md->chunk_list[k].vectors[i],md->chunk_list[k].size);
					nd->statistic->variance=CalculateVariance(md->chunk_list[k].vectors[i],md->chunk_list[k].size,nd->statistic->mean);
					nd->statistic->standard_deviation=sqrt(nd->statistic->variance);

					/***/

#ifdef INSERT		
					InsertNode(address,nd);
#endif				
				}

				// This is to complete the calculation of the first level of the data canopy. 

				if(j==md->num_col)
					continue;

				/*Create a new node. For level two, the identifier is 2^i + 2^j*/

				node* nd = new node();
				nd->statistic = new stat();
				pos_int address = GetAddress(pow(2,i)+pow(2,j),k);
				nd->identifier = address;

			
			
				num++;
			
				/***/

				nd->statistic->correlation=CalculateCorrelation(md->chunk_list[k].vectors[i],md->chunk_list[k].size,md->chunk_list[k].vectors[j],md->chunk_list[k].size);
				
				/***/
#ifdef INSERT	

				InsertNode(address,nd);

#endif
			}
			is_level_one_Calculated=true;
		}
	}
	is_level_one_built=true;
	is_level_two_built=true;

	return 1;
}

error_code DataCanopy::BuildAll(pos_int start_chunk, pos_int end_chunk){

	int num = 0;
	pos_int canopy_size = pow(2,(md->num_col));

	/*Build the first two-levels as they are required*/
	
	if(!is_level_one_built)
		BuildLevelOne(start_chunk,end_chunk);
	
	if(!is_level_two_built)
		BuildLevelTwo(start_chunk,end_chunk);

	
	/***/
	
	for (pos_int i = 1; i < canopy_size ; ++i){
		
		/*Skip level two, as we have already constructed it*/
		if(IsLevelOne(i)){
			continue;
		}
		if(IsLevelTwo(i)){
			continue;
		}

		/**/
		
		/*Create a new node*/

		node* nd = new node();
		nd->statistic = new stat();
		nd->identifier = i;

		/***/

		/*Access all the values that are required to to create a certain node. The assumption here is that 
		you will need to access all nodes in the lowest level that correspond to the columns*/

		
		for (pos_int k = start_chunk; k < end_chunk; ++k){
			num++;
			nd->statistic->num+=CalculateMultiCorrelation(i,k);
#ifdef INSERT			

			InsertNode(GetAddress(i,k),nd);

#endif
		}
			

		/***/
	}

#ifdef INSERT
	//assert(GetCanopySize()==(pow(md->num_col,2) * md->num_chun));
#endif
	return 1;
}


pos_int DataCanopy::GetCanopySize(){
	return nodes.size();
}

pos_int DataCanopy::GetNumChunk(){
	return md->num_chun;
}

float DataCanopy::CalculateCorrelation(column* x, column* y){
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


float DataCanopy::CalculateCorrelation(data* x, pos_int size_x, data* y, pos_int size_y){
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

float DataCanopy::CalculateMean(data* x, pos_int size_x){

	int sum = 0;
	for(pos_int i=0; i<size_x; ++i){
		sum+=x[i];
	}
	return sum*1.0/size_x*1.0;
}

float DataCanopy::CalculateVariance(data* x, pos_int size_x,float mean){

	int sum = 0;
	for(pos_int i=0; i<size_x; ++i){
		sum+=pow(mean-(x[i]*1.0),2);
	}
	return sum*1.0/size_x*1.0;
}

float DataCanopy::CalculateMultiCorrelation(pos_int node_id, int chunk_number){

	for(pos_int j = 0 ;j < md->num_col; ++j){
		
		/*Check if the particular column is of relevance to the ID*/
		
		if(( (node_id>>j) &1) == 1){
			
			/*Check what other columns are in the ID, which should be paired with this*/

			for(pos_int i = j+1; i < md->num_col; ++i){

				if(( (node_id>>i) &1) == 1){
					GetNodeValue(GetAddress(pow(2,i)+pow(2,j),chunk_number));

				}
			}			
		}
	}
	return 0;
}
error_code DataCanopy::InsertNode(pos_int address, node* nd){

#ifndef LOCKFREE
	pthread_mutex_lock(&mutex);

	std::pair<pos_int,node*> to_insert(address,nd);
	nodes.insert(to_insert);

	pthread_mutex_unlock(&mutex);

#else

	concurrent_map::accessor a;
	nodes.insert(a,address);
	a->second=nd;

#endif
#ifdef PRINT_FOR_DEMO
	pos_int full = (pow( 2,md->num_col) -1 ) * md->num_chun;

	float built=GetCanopySize()*1.0/full*1.0*100;
	//cout<<built<<endl;
	if (built-previous_print>=2){
		cout<<built<<"|"<<built*100<<"\n";
		previous_print=built;
	}
	if (built==100){
		cout<<built<<"|"<<built*100<<"\n";
		previous_print=built;
	}
#endif
	return 1;
}





















