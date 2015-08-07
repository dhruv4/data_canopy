#include "canopyInteractor.hh"

CanopyInteractor::CanopyInteractor(DataCanopy* cp){
	canopy = cp;
}


stat* CanopyInteractor::GetStat(pos_int chunk_number, pos_int level_number, pos_int* columns){

	pos_int address = 0;

	for (pos_int i = 0; i < level_number; ++i){
		
		address += pow(2,columns[i]);

	}

	node* nd = canopy->GetNode( canopy->GetAddress(address,chunk_number) );
	return nd->statistic;

}