#ifndef CANOPY_BUILDER_HH
#define CANOPY_BUILDER_HH

#include <assert.h>
#include <pthread.h>

#include "config.h"
#include "data.hh"
#include "canopy.hh"

/*
*  The input given to the thread building the data canopy
*/


struct threadInput{
	pos_int start_chunk;
	pos_int end_chunk;
	DataCanopy* dc;
	int buildMode; // 1 -- LevelOne; 2 -- Level 2; 12 -- Level 1 and 2; 3 -- All levels;
};

/*
*	This class is responsible for building the data canopy
*/

class CanopyBuilder{
	
	private:
		int nthreads;
		DataCanopy * canopy;
		int BuildThreaded( int buildMode);

	public:
		CanopyBuilder(DataCanopy* dc, int threads);
		
		int BuildLevelOne();
		int BuildLevelTwo();
		int BuildLevelOneTwo();
		int BuildAll();



};

#endif