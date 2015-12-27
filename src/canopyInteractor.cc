#include "canopyInteractor.hh"

CanopyInteractor::CanopyInteractor(DataCanopy* cp){
	canopy = cp;
}

void CanopyInteractor::HandleInput(string input){

	/*
	*	If the user wishes to exit the program
	**/

	if(strncmp(quit,input.c_str(),4)==0){
		exit(0);
	}

	/*
	*	Else we assume it is a query
	**/

	stat* result=ParseRequest(input.c_str(),input.size());
	cout<<"avg: "<<result->mean<<endl;
	cout<<"var: "<<result->variance<<endl;
	cout<<"std: "<<result->standard_deviation<<endl;
	cout<<"cor: "<<result->correlation;

}

void CanopyInteractor::StartTerminal(){
	
	cout<<message<<endl;
	string input;
	while(true){
		cout<<endl<<prompt;
		cin>>input;
		HandleInput(input);
	}

}

/**
*	Fetches statistics based on the chunk number, level_number and the set of columns. 
*/

stat* CanopyInteractor::GetStat(pos_int chunk_number, pos_int level_number, pos_int* columns){

	/*
	*	Based on the input, construct the address of that particular node in the data canopy.
	*	At the end of this for loop, address is a bit string where i, i belongs to columns is
	*	1. 
	**/

	pos_int address = 0; // 00....00

	for (pos_int i = 0; i < level_number; ++i){
		
		address += pow(2,columns[i]);

	} 

	/*
	*	Once the address has been constructed, you can query the data canopy.
	*/

	node* nd = canopy->GetNode( canopy->GetAddress(address,chunk_number) );
	return nd->statistic;

}

/** 
*	A very bad parser. 
*	@Dhruv: Check that it only accepts the right kind of input. You can do that using Regex.
*		
*/

//Regex for collecting chunk and level: \([0-9]+)(?=;)\g
//Regex for collecting columns: \([0-9]+)(?=,)|([0-9]+)(?=})\g

stat* CanopyInteractor::ParseRequest(const char* request,int length){

	char parse_string[length];
	strcpy(parse_string,request);

	regex e ("(\\d+)(?=;)|([0-9]+)(?=,)|([0-9]+)(?=})");

	sregex_iterator next(parse_string.begin(), parse_string.end(), e);
	sregex_iterator end;

	smatch match = *next;
	pos_int chunk_number = stoi(match.str());
	next++;
	match = *next;
	pos_int level_number = stoi(match.str());
	next++;

	pos_int* columns = new pos_int[level_number];

	pos_int i=0;

	while (next != end) {
		match = *next;
		columns[i] = stoi(match.str());
		next++;
		i++;
	}



	return GetStat(chunk_number,level_number,columns);



}