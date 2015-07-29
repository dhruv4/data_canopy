#ifndef CANOPY_HH
#define CANOPY_HH


#include <math.h>
#include <unordered_map>
#include <assert.h>
#include <pthread.h>
#include <assert.h>



#include "data.hh"
#include "config.h"
#include "tbb/concurrent_hash_map.h"
using namespace tbb;

/*
*	Structure that defines hashing for the user's type
*/

struct MyHashCompare {
    static size_t hash( const pos_int& x ) {
        return x;
    }

    //! True if numbers are equal
    
    static bool equal( const pos_int& x, const pos_int& y ) {
        return x==y;
    }

};



/*
* 	The struct that contains the stats
*/

struct stat{

	pos_int num=0;
	float mean=0.0;
	float variance=0.0;
	float standard_deviation=0.0;
	float correlation=0.0;

};

/*
*	Node of the data canopy
*/

struct node{

	pos_int identifier;
	stat* statistic;

};

typedef concurrent_hash_map<pos_int,node*,MyHashCompare> concurrent_map;

class DataCanopy{

private:
	
	node** canopies;					/*Store as an array indexed by the node identifier*/
	
#ifndef LOCKFREE
	unordered_map<pos_int,node*> nodes;	/*Store as a hash map*/
#else	
	concurrent_map nodes;
#endif


	mdata* md;
	pos_int log_num_chun;
	
	bool is_level_one_built;
	bool is_level_two_built;

	pthread_mutex_t mutex;

	//int percent_built=0;
	//int print after;
	
	error_code InsertNode(pos_int address, node* node);
	node* GetNode(pos_int address);

	float previous_print=0;
	
	bool IsLevelOne(pos_int x);
	bool IsLevelTwo(pos_int x);

	
	float CalculateCorrelation(column* x, column* y);
	float CalculateCorrelation(data* x, pos_int size_x, data* y, pos_int size_y);
	float CalculateMean(data* x, pos_int size_x);
	float CalculateVariance(data* x, pos_int size_x,float mean);
	float CalculateMultiCorrelation(pos_int node_id, int chunk_number);

	pos_int GetNodeValue(pos_int add);

	
public:
	
	DataCanopy(mdata* md);
	pos_int ProbeCanopy();
	
	
	error_code BuildLevelOne(pos_int start_chunk, pos_int end_chunk);
	error_code BuildLevelTwo(pos_int start_chunk, pos_int end_chunk);
	error_code BuildLevelOneTwo(pos_int start_chunk, pos_int end_chunk);
	error_code BuildAll(pos_int start_chunk, pos_int end_chunk);
	
	pos_int GetCanopySize();
	pos_int GetNumChunk();
	pos_int GetAddress(pos_int node, pos_int chunk);

	//temp functions

};

#endif
