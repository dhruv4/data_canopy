#ifndef STAT_HH
#define STAT_HH


#include <math.h>
#include <assert.h>

#include "data.hh"
#include "config.h"



/*
* 	The struct that contains the stats
*/
struct stat{

	pos_int num=0;
	float mean=0.0;
	float variance=0.0;
	float standard_deviation=0.0;
	float corelation=0.0;

};


float calculateCorelation(column* x, column* y);
float calculateCorelation(data* x, pos_int size_x, data* y, pos_int size_y);
float calculateMean(data* x, pos_int size_x);
float calculateVariance(data* x, pos_int size_x,float mean);
float calculateMultiCorrelation(pos_int node_id, int chunk_number, DataCanopy* dc);




#endif