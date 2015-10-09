#ifndef CANOPY_HH
#define CANOPY_HH


#include <math.h>
#include <unordered_map>
#include <assert.h>
#include <pthread.h>
#include <assert.h>
#include <fstream>


#include "data.hh"
#include "config.h"
#include "tbb/concurrent_hash_map.h"
using namespace tbb;





/**
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


/**
* 	A struct for storing statitics. This can be extended with more types of data sets based on the users
*	interest.
*/

struct stat{

	pos_int num=0;
	float mean=0.0;
	float variance=0.0;
	float standard_deviation=0.0;
	float correlation=0.0;

};


/**
*	One node of the data canopy. It contains an identifier as well as a struct 
* 	containing relevant statistics, 
*/

struct node{

	pos_int identifier;
	stat* statistic;

};

/**
*	A typedef of a concurrent hash_map to improve scaling on multiple nodes
*/

typedef concurrent_hash_map<pos_int,node*,MyHashCompare> concurrent_map;

/**
*	The data canopy class. It stores the data canopy as well as provide simple access methods 
*	to the data canopy. 
*/

class DataCanopy{

	/*** Data variables ***/
	//TODO: Should they be public ? 

	mdata* md;
	pos_int log_num_chun;

	/***/

	/*** data structures for data canopy ***/

private:
	
#ifndef LOCKFREE
	unordered_map<pos_int,node*> nodes;	/*Store as a hash map*/
	pthread_mutex_t mutex;				/*The mutex for the locking version*/
#else	
	concurrent_map nodes;				/*The concurent hash table from TBB*/
	
#endif

	/**Bool variables to determine the percentage of the data canopy that is built*/
	
	bool is_level_one_built;
	bool is_level_two_built;

	/***/
	
	bool IsLevelOne(pos_int x);
	bool IsLevelTwo(pos_int x);

	/*** Node getters and setters ***/ 

	error_code InsertNode(pos_int address, node* node);
	pos_int GetNodeValue(pos_int add);

	/***/ 

	/*** variables for demo purposes ***/

	float previous_print=0;
	ofstream output_file;
	ifstream print_file;

	/***/

	/*** Stat Functions (Should be a seperate class?) ***/
	
	float CalculateCorrelation(column* x, column* y);
	float CalculateCorrelation(data* x, pos_int size_x, data* y, pos_int size_y);
	float CalculateMean(data* x, pos_int size_x);
	float CalculateVariance(data* x, pos_int size_x,float mean);
	float CalculateMultiCorrelation(pos_int node_id, int chunk_number);

	/***/

	
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

	node* GetNode(pos_int address);
	
};

#endif
