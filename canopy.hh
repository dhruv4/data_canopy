#ifndef CANOPY_HH
#define CANOPY_HH


#include <math.h>
#include <unordered_map>
#include <assert.h>
#include <pthread.h>

#include "stat.hh"
#include "data.hh"
#include "config.h"





/*
*	Node of the data canopy
*/

struct node{

	pos_int identifier;
	stat* statistic;

};

class DataCanopy{

private:
	
	node** canopies;					/*Store as an array indexed by the node identifier*/
	unordered_map<pos_int,node*> nodes;	/*Store as a hash map*/
	mdata* md;
	pos_int log_num_chun;
	
	bool is_level_one_built;
	bool is_level_two_built;
	
	pos_int GetAddress(pos_int node, pos_int chunk);
	bool IsLevelOne(pos_int x);
	bool IsLevelTwo(pos_int x);

	void BuildLevelOne(void* thread_input);

	
public:
	
	DataCanopy(mdata* md);
	pos_int ProbeCanopy();
	
	
	error_code BuildLevelOne(pos_int start_chunk, pos_int end_chunk);
	error_code BuildLevelTwo(pos_int start_chunk, pos_int end_chunk);
	error_code BuildLevelOneTwo(pos_int start_chunk, pos_int end_chunk);
	error_code BuildAll(pos_int start_chunk, pos_int end_chunk);
	
	pos_int GetCanopySize();
	pos_int GetNumChunk();

	//temp functions
	pos_int GetNodeValue(pos_int add);

};

#endif
