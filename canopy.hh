#ifndef CANOPY_HH
#define CANOPY_HH


#include <math.h>
#include <unordered_map>
#include <assert.h>

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

public:
	
	DataCanopy(mdata* md);
	error_code Initialize();
	error_code MakeCanopy();
	error_code MakeCanopyCacheFriendly();
	pos_int ProbeCanopy();
	
	
	error_code BuildLevelOne();
	error_code BuildLevelTwo();
	error_code BuildLevelOneTwo();
	error_code BuildAll();

	pos_int GetCanopySize();

	//temp functions
	pos_int GetNodeValue(pos_int add);

};

#endif
