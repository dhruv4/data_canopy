#ifndef GENERATOR_HH
#define GENERATOR_HH


#include <time.h>


#include "data.hh"
#include "config.h"

error_code generate_cont(data** vector, pos_int size, int start);
error_code generate_const(data** vector, pos_int size, int constant);
error_code generate_rand(data** vector, pos_int size);

#endif