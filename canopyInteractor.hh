#ifndef CANOPY_INTERACTOR
#define CANOPY_INTERACTOR

#include "config.h"
#include "data.hh"
#include "canopy.hh"

class CanopyInteractor{

private:
	DataCanopy* canopy;


public:
	CanopyInteractor(DataCanopy* cp);

	stat* GetStat(pos_int chunk_number, pos_int level_number, pos_int* columns);

};























#endif