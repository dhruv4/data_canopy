#ifndef GENERATOR_HH
#define GENERATOR_HH


#include <time.h>


#include "data.hh"
#include "config.h"

/*
*	Generate numbers with different properties.
**/

error_code generate_cont(data** vector, pos_int size, int start);
error_code generate_const(data** vector, pos_int size, int constant);
error_code generate_rand(data** vector, pos_int size);

/**
*	@Dhruv: implement these functions in generator.cc
*/

error_code generate_normal(data** vector, pos_int size, float mean, float variance); // Normal distribtuion data
error_code generate_exponential(data** vector, pos_int size, float lambda); // Exponential distribution data
error_code generate_bernoulli(data** vector, pos_int size, float p); // Collections of zeros and ones

#endif