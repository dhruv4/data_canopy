#include "data.hh"

error_code create_column(column* col, pos_int identifier, pos_int size, data* vector){

	col = new column();
	
	col->identifier = identifier;
	col->size = size;
	col->vector = vector;

	return 1;
}

error_code create_chunk(chunk* chun, pos_int identifier, pos_int size, pos_int num_col, data** vectors){

	chun = new chunk();
	
	chun->identifier = identifier;
	chun->size = size;
	chun->num_col = num_col;	
	vectors = vectors;

	return 1;
}

error_code create_mdata(mdata* md, column* column_list, chunk* chunk_list){
	
	md = new mdata();

	md->column_list = column_list;
	md->chunk_list = chunk_list;

	return 1;
}

error_code chunkify(mdata** md, column* column_list, pos_int size, pos_int num_col){

	
	*md = (mdata*)malloc(sizeof(mdata));



	pos_int num_chunk = column_list[0].size/size;
	
	(*md)->num_chun = num_chunk;
	(*md)->num_col=num_col;
	(*md)->chunk_list = (chunk*)malloc(num_chunk*sizeof(chunk));
	(*md)->column_list = column_list;

	for (pos_int i=0; i<num_chunk; ++i ){
		(*md)->chunk_list[i].vectors = (data**)malloc(num_col*sizeof(data*));
		(*md)->chunk_list[i].identifier=i;
		(*md)->chunk_list[i].size=size;
		
		/*For the last chunk, assign the remainder of the size*/
		
		if(i==num_chunk-1)
			(*md)->chunk_list[i].size=(*md)->column_list[0].size - i*size;
		
		(*md)->chunk_list[i].num_col=num_col;

		for (pos_int j=0; j<num_col; ++j){
			(*md)->chunk_list[i].vectors[j]=&column_list[j].vector[i*size];

		}
	}

	return 1;
}

error_code pretty_print_md(mdata* md){

	cout<<"***  ***  ***"<<endl;
	cout<<"Num of Columns: "<<md->num_col<<endl;
	cout<<"Num of Chunks: "<<md->num_chun<<endl;
	
	for (pos_int i = 0; i < md->num_chun; ++i){
		
		cout<<"chunk "<<i<<endl;
		
		for (pos_int j = 0; j < md->num_col; ++j){
			
			cout<<"\t";
			cout<<md->chunk_list[i].vectors[j][0]; 
		}
		cout<<endl;

		for (pos_int j = 0; j < md->num_col; ++j){
			
			cout<<"\t";
			cout<<"."; 
		}
		cout<<endl;
		for (pos_int j = 0; j < md->num_col; ++j){
			
			cout<<"\t";
			cout<<"."; 
		}
		cout<<endl;
		for (pos_int j = 0; j < md->num_col; ++j){
			
			cout<<"\t";
			cout<<"."; 
		}
		cout<<endl;
		for (pos_int j = 0; j < md->num_col; ++j){
			
			cout<<"\t";
			cout<<md->chunk_list[i].vectors[j][md->chunk_list[i].size-1]; 
		}
		cout<<endl;

	}
	return 1;

}



error_code pretty_print_cols(column* col, pos_int num_col){

	for (pos_int j = 0; j < num_col; ++j){
		cout<<"\t";
		cout<<col[j].column_name; 
	}
	cout<<endl;
	for (pos_int j = 0; j < num_col; ++j){
		cout<<"\t";
		cout<<col[j].vector[0]; 
	}
	cout<<endl;

	for (pos_int j = 0; j < num_col; ++j){
		
		cout<<"\t";
		cout<<"."; 
	}
	cout<<endl;
	for (pos_int j = 0; j < num_col; ++j){
		
		cout<<"\t";
		cout<<"."; 
	}
	cout<<endl;
	for (pos_int j = 0; j < num_col; ++j){
		
		cout<<"\t";
		cout<<"."; 
	}
	cout<<endl;
	for (pos_int j = 0; j < num_col; ++j){
		
		cout<<"\t";
		cout<<col[j].vector[col[j].size-1]; 
	}
	cout<<endl;
	return 1;
}


vector<string>& divide(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> divide(const string &s, char delim) {
    vector<string> elems;
    divide(s, delim, elems);
    return elems;
}


error_code load_file(char* filename, column** columns, pos_int num_col, pos_int size_col){

	string line;
	ifstream my_file (filename);

	for (pos_int i = 0; i < num_col; ++i){
		(*columns)[i].size = size_col;
		(*columns)[i].vector = (data*)malloc(size_col*sizeof(data));
	}
	
	int posn = -1;
	
	if(my_file.is_open()){
		while ( getline (my_file,line,';') && size_col != 0){

			
			vector <string> items = divide(line,',');
			assert(items.size()==num_col);
			
			for (pos_int i = 0; i < num_col; ++i){
			
				if(posn == -1){
					(*columns)[i].column_name = new char[strlen(items[i].c_str())+1];
					strcpy((*columns)[i].column_name,items[i].c_str());
				}else{
					(*columns)[i].vector[posn] = stoi(items[i]);
				}
			}
			if (posn != -1)
				size_col--;
			posn++;	
			
		}
			
	}
	return 0;
}