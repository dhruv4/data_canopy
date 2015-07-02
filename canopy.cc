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
}

pos_int DataCanopy::GetAddress(pos_int node, pos_int chunk){
	return node<<log_num_chun|chunk;
}

bool DataCanopy::IsLevelOne(pos_int x){
	while (((x & 1) == 0) && x > 1) /* While x is even and > 1 */
   		x >>= 1;
 	return (x == 1);
}


error_code DataCanopy::MakeCanopy(){

	pos_int canopy_size = pow(2,(md->num_col));
	
	int num = 0;

	//cout<<canopy_size<<endl;
	for (pos_int k = 0; k < md->num_chun; ++k){
		for (pos_int i = 1; i < canopy_size ; ++i){
			
			node* nd = new node();
			nd->identifier = i;
			std::pair<pos_int,node*> to_insert(i,nd);
			nodes.insert(to_insert);
			for(int j = 0 ;j < 32; ++j){

				if(( (i>>j) &1) == 1){
					num++;
					nd->statistic->num=scan(md->chunk_list[0].vectors[j],md->chunk_list[k].size);
				}
			}
		}
	}
	return 1;

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


pos_int DataCanopy::GetCanopySize(){
	return nodes.size();
}

error_code DataCanopy::Initialize(){
	int n = 0;
	int m = 0;
	for (pos_int i = 0; i < md->num_col; ++i){
		for (pos_int j = i; j < md->num_col; ++j){
			for (pos_int k = 0; k < md->num_chun; ++k){
				if(i==j){
					
				/*****/	

					node* nd = new node();
					nd->statistic = new stat();
					nd->identifier = i;

				/*****/

					nd->statistic->num+=scan(md->chunk_list[k].vectors[i],md->chunk_list[k].size);
					std::pair<pos_int,node*> to_insert(GetAddress(1<<i,k),nd);
					nodes.insert(to_insert);
					n++;
					continue;
				}
				
				/*****/
				
				pos_int posn_1 = 1<<i;
				pos_int posn_2 = 1<<j;
				pos_int posn = posn_1|posn_2;
				
				node* nd = new node();
				nd->statistic = new stat();
				nd->identifier = posn;
				
				/*****/
				
				nd->statistic->corelation=calculateCorelation(md->chunk_list[k].vectors[i],md->chunk_list[k].size,md->chunk_list[k].vectors[j],md->chunk_list[k].size);
				std::pair<pos_int,node*> to_insert(GetAddress(posn,k),nd);
				nodes.insert(to_insert);
				m++;
			}
		}		
	}
	
	cout<<nodes.size()<<",,canopy_size"<<endl;
	return 1;
}

error_code DataCanopy::BuildLevelOne(){

	//pos_int canopy_size = pow(2,(md->num_col));
	int num = 0; 

	for (pos_int i = 0; i<md->num_col; ++i){

		

		for (pos_int k = 0; k < md->num_chun; ++k){
			num++;

			/*Create a new node. For level one the identifier is 2^i*/
			
			node* nd = new node();
			nd->statistic = new stat();
			nd->identifier = pow(2,i);
			
			/***/

			nd->statistic->mean=calculateMean(md->chunk_list[k].vectors[i],md->chunk_list[k].size);
			nd->statistic->variance=calculateVariance(md->chunk_list[k].vectors[i],md->chunk_list[k].size,nd->statistic->mean);
			nd->statistic->standard_deviation=sqrt(nd->statistic->variance);

			/***/

#ifdef INSERT			
			std::pair<pos_int,node*> to_insert(GetAddress(pow(2,i),k),nd);
			nodes.insert(to_insert);
#endif

		}
	}

	return 1;

}

error_code DataCanopy::BuildLevelTwo(){

	
	//pos_int canopy_size = pow(2,(md->num_col));
	int num = 0; 

	for (pos_int i = 0; i<md->num_col; ++i){
		for (pos_int j = i+1; j<md->num_col; ++j){
			
			/*Create a new node. For level two the identifier is 2^i + 2^j*/

			node* nd = new node();
			nd->statistic = new stat();
			nd->identifier = pow(2,i)+pow(2,j);

			for (pos_int k = 0; k < md->num_chun; ++k){
			
				num++;
			
				/***/

				nd->statistic->corelation=calculateCorelation(md->chunk_list[k].vectors[i],md->chunk_list[k].size,md->chunk_list[k].vectors[j],md->chunk_list[k].size);
				
				/***/
#ifdef INSERT			
				std::pair<pos_int,node*> to_insert(GetAddress(pow(2,i)+pow(2,j),k),nd);
				nodes.insert(to_insert);
#endif
			}
		}
	}
	return 1;


}

error_code DataCanopy::BuildLevelOneTwo(){
	//pos_int canopy_size = pow(2,(md->num_col));
	int num = 0; 
	bool is_level_one_calculated;
	
	for (pos_int i = 0; i<md->num_col; ++i){
		is_level_one_calculated = false;

		for (pos_int j = i+1; j<md->num_col+1; ++j){
			for (pos_int k = 0; k < md->num_chun; ++k){
			
				//cout<<i<<" "<<j<<endl;
			
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

				// This is to allow the calculation of the first level of the data canopy. 

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
	return 1;
}

error_code DataCanopy::MakeCanopyCacheFriendly(){

	pos_int canopy_size = pow(2,(md->num_col));
	
	int num = 0;
	
	for (pos_int i = 1; i < canopy_size ; ++i){
		
		/*Create a new node*/
		node* nd = new node();
		nd->statistic = new stat();
		nd->identifier = i;

#ifndef COMPOSABLE
		for(pos_int j = 0 ;j < md->num_col; ++j){

			if(( (i>>j) &1) == 1){
				for (pos_int k = 0; k < md->num_chun; ++k){
					num++;
					nd->statistic->num+=scan(md->chunk_list[k].vectors[j],md->chunk_list[k].size);
#ifdef INSERT			
					std::pair<pos_int,node*> to_insert(GetAddress(i,k),nd);
					nodes.insert(to_insert);
#endif
				}
			}
		}
		
#else
		if(isLevelOne(i)){

			for(pos_int j = 0 ;j < md->num_col; ++j){

				if(( (i>>j) &1) == 1){
					for (pos_int k = 0; k < md->num_chun; ++k){
						num++;
						/***/

						nd->statistic->mean=calculateMean(md->chunk_list[k].vectors[j],md->chunk_list[k].size);
						nd->statistic->variance=calculateVariance(md->chunk_list[k].vectors[j],md->chunk_list[k].size);
						nd->statistic->standard_deviation=sqrt(nd->statistic->variance);

						/***/
#ifdef INSERT			
						std::pair<pos_int,node*> to_insert(GetAddress(i,k),nd);
						nodes.insert(to_insert);
#endif
					}
				}
			}
		}else{
			for(pos_int j = 0 ;j < md->num_col; ++j){

				if(( (i>>j) &1) == 1){
					int temp =(1<<j);
					for (pos_int k = 0; k < md->num_chun; ++k){
						num++;
						nd->statistic->num+=GetNodeValue(GetAddress(temp,k));
	#ifdef INSERT			
						std::pair<pos_int,node*> to_insert(GetAddress(i,k),nd);
						nodes.insert(to_insert);
	#endif
					}
				}
			}
		}
#endif
	}
	cout<<nodes.size()<<",,canopy_size"<<endl;
	return 1;
	
}