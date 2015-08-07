
#ifndef DATA_HH
#define DATA_HH

#include <iostream>
#include <cstdlib>

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <assert.h>

#include "config.h"

using namespace std;


typedef unsigned long long pos_int;
typedef int data;
typedef int error_code;

/*
	Internal representation of the columns in the data canopy
*/
struct column{
	char* column_name;		/*The name of the column that we are interested in */
	pos_int identifier; 	/*A number that identifes the column*/ 
	pos_int size;			/*Size of the column*/
	data* vector;			/*Pointer to the data array*/
};

/*
	A chunk is composed of multiple pieces of a column.
*/

struct chunk{
	pos_int identifier;
	pos_int size;
	pos_int num_col;
	data** vectors;
};

/*
	stores the metadata of the entire data canopy
*/

struct mdata{
	column* column_list;
	chunk*  chunk_list;
	pos_int num_col;
	pos_int num_chun;
};

/*
	Create and manipulate data
*/

error_code load_data(char* filename,pos_int num_col);
error_code create_column(column* col, data* vector, pos_int size, pos_int identifier);
error_code create_chunk(chunk* chun, pos_int identifier, pos_int size, pos_int num_col, data** vectors);
error_code create_mdata(mdata* md, column* column_list, chunk* chunk_list);
error_code chunkify(mdata** md, column* column_list, pos_int size, pos_int num_col);
error_code pretty_print_md(mdata* md);
error_code pretty_print_cols(column* col, pos_int num_col);
error_code load_file(char* filename, column** columns, pos_int num_col, pos_int num_rows);

#endif
