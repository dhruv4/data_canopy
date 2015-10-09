#ifndef CANOPY_INTERACTOR
#define CANOPY_INTERACTOR

#include <string>

#include "config.h"
#include "data.hh"
#include "canopy.hh"

/**
*	Once the data canopy has been constructed, this class can be used to interact with it. 
* 	Currently, it also supports an implementation for a basic terminal. Currently, the terminal
*/

/**
*	The form of input we react to is: <Column_number>;<level_number>;{<comma-seperated list of columns>}
*	e.g: 1;1;{10} -- 1;2;{2,3}
*
*/

class CanopyInteractor{

private:
	DataCanopy* canopy;
	const char* message=
	"\n\n\n\n"
	"********************************************************************************************\n"
	"********************************************************************************************\n"
	"*                                                                                          *\n"
	"*                               DATA CANOPY VERSION 1.0                                    *\n"
	"*                                                                                          *\n"
	"********************************************************************************************\n"
	"********************************************************************************************\n"
	"\n\n\n\n";
	const char* prompt=" dc> ";
	const char* quit="quit";

	void HandleInput(string);


public:
	CanopyInteractor(DataCanopy* cp);

	stat* GetStat(pos_int chunk_number, pos_int level_number, pos_int* columns);
	stat* ParseRequest(const char* request,int length);
	void StartTerminal();

};























#endif