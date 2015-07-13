#include "canopy.hh"

/**
*	START--Temporary functions
*/

pos_int DataCanopy::GetNodeValue(pos_int add){
	return nodes.find(add)->second->statistic->num;
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
	return node<<log_num_chun|chunk;
}

bool DataCanopy::IsLevelOne(pos_int x){
	while (((x & 1) == 0) && x > 1) /* While x is even and > 1 */
   		x >>= 1;
 	return (x == 1);
}

bool DataCanopy::IsLevelTwo(pos_int x){
	while (((x & 1) == 0) && x > 1) /* While x is even and > 1 */
   		x >>= 1;
 	return (x == 2);
}

pos_int DataCanopy::ProbeCanopy(){
	
	pos_int n=0;
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
	return n;	

}



error_code DataCanopy::BuildLevelOne(pos_int start_chunk, pos_int end_chunk){

	int num = 0; 

	for (pos_int i = 0; i<md->num_col; ++i){

		for (pos_int k = start_chunk; k < end_chunk; ++k){
		
			num++;

			/*Create a new node. For level one the identifier is 2^i*/
			
			node* nd = new node();
			nd->statistic = new stat();
			nd->identifier = pow(2,i);
			
			/***/

			/*Calculate and store statistics for each of the nodes based on the 
			data it accesses.*/

			nd->statistic->mean=calculateMean(md->chunk_list[k].vectors[i],md->chunk_list[k].size);
			nd->statistic->variance=calculateVariance(md->chunk_list[k].vectors[i],md->chunk_list[k].size,nd->statistic->mean);
			nd->statistic->standard_deviation=sqrt(nd->statistic->variance);

			/***/

#ifdef INSERT	
			
			/*Insert the node in the data canopy*/

			std::pair<pos_int,node*> to_insert(GetAddress(pow(2,i),k),nd);
			nodes.insert(to_insert);

			/***/
#endif

		}
	}
	is_level_one_built=true;
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

				nd->statistic->corelation=calculateCorelation(md->chunk_list[k].vectors[i],md->chunk_list[k].size,md->chunk_list[k].vectors[j],md->chunk_list[k].size);
				
				/***/
#ifdef INSERT			
				std::pair<pos_int,node*> to_insert(address,nd);
				nodes.insert(to_insert);
#endif
			}
		}
	}
	is_level_two_built=true;
	return 1;


}


error_code DataCanopy::BuildLevelOneTwo(pos_int start_chunk, pos_int end_chunk){

	int num = 0; 
	bool is_level_one_calculated;
	
	for (pos_int i = 0; i<md->num_col; ++i){
		is_level_one_calculated = false;

		for (pos_int j = i+1; j<md->num_col+1; ++j){
			for (pos_int k = start_chunk; k < end_chunk; ++k){
			
			
				if (is_level_one_calculated == false){

					/*Create a new node. For level one the identifier is 2^i*/
					
					node* nd = new node();
					nd->statistic = new stat();
					pos_int address = GetAddress(pow(2,i),k);
					nd->identifier = address;
					
					//cout<<pow(2,i)<<endl;
					/***/

					nd->statistic->mean=calculateMean(md->chunk_list[k].vectors[i],md->chunk_list[k].size);
					nd->statistic->variance=calculateVariance(md->chunk_list[k].vectors[i],md->chunk_list[k].size,nd->statistic->mean);
					nd->statistic->standard_deviation=sqrt(nd->statistic->variance);

					/***/

#ifdef INSERT			
					std::pair<pos_int,node*> to_insert(address,nd);
					nodes.insert(to_insert);
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

				nd->statistic->corelation=calculateCorelation(md->chunk_list[k].vectors[i],md->chunk_list[k].size,md->chunk_list[k].vectors[j],md->chunk_list[k].size);
				
				/***/
#ifdef INSERT			
				std::pair<pos_int,node*> to_insert(address,nd);
				nodes.insert(to_insert);
#endif
			}
			is_level_one_calculated=true;
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
	
	for (pos_int i = md->num_col+1; i < canopy_size ; ++i){
		
		/*Skip level two, as we have already constructed it*/
		
		if(IsLevelTwo(i))
			continue;

		/**/
		
		/*Create a new node*/

		node* nd = new node();
		nd->statistic = new stat();
		nd->identifier = i;

		/***/

		/*Access all the values that are required to to create a certain node. The assumption here is that 
		you will need to access all nodes in the lowest level that correspond to the columns*/

		for(pos_int j = 0 ;j < md->num_col; ++j){

			if(( (i>>j) &1) == 1){
				int temp =(1<<j);
				for (pos_int k = start_chunk; k < end_chunk; ++k){
					num++;
					nd->statistic->num+=GetNodeValue(GetAddress(temp,k));
#ifdef INSERT			
					std::pair<pos_int,node*> to_insert(GetAddress(i,k),nd);
					nodes.insert(to_insert);
#endif
				}
			}
		}

		/***/
	}
	return 1;
}


pos_int DataCanopy::GetCanopySize(){
	return nodes.size();
}

pos_int DataCanopy::GetNumChunk(){
	return md->num_chun;
}
