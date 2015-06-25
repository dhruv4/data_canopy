#include <math.h>
#include <unordered_map>
#include <assert.h>

#ifndef DATA_HH
#include "data.hh"
#define DATA_HH
#endif
#include "config.h"
float calculateCorelation(column* x, column* y);


/*
* 	The struct that contains the stats
*/
struct stat{

	pos_int num=0;
	float mean=0.0;
	float corelation=0.0;

};

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
	pos_int getAddress(pos_int node, pos_int chunk);

public:
	
	DataCanopy(mdata* md);
	error_code initialize();
	error_code makeCanopy();
	error_code makeCanopyCacheFriendly();
	pos_int probeCanopy();
	bool isLevelOne(pos_int x);

	//temp functions
	pos_int getNodeValue(pos_int add);
};




