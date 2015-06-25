#ifndef DATA_HH
#include "data.hh"
#define DATA_HH
#endif
#include <time.h>


#include "config.h"

error_code generate_cont(data** vector, pos_int size, int start);
error_code generate_const(data** vector, pos_int size, int constant);
error_code generate_rand(data** vector, pos_int size);