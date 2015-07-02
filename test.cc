#include <math.h>

#include "config.h"
#include "canopy.hh"
#include "generator.hh"
#include "./tools/run_perf.hh"
#include "./tools/timer.hh"

using namespace std;

int main(int argc,  char** argv){
	
	if(argc !=4)
		return -1;

	perfProfiler* p = new perfProfiler("cycles,cache-misses",false);
	timer* t = new timer();

	pos_int num_col = atoi(argv[1]); 
	pos_int size_col = atoi(argv[2]);
	pos_int size_chunk = atoi(argv[3]);

	cout<<num_col<<",,num_col"<<endl;
	cout<<size_col<<",,size_col"<<endl;
	cout<<size_chunk<<",,size_chunk"<<endl;

	column* columns = (column*)malloc(num_col*sizeof(column));
	
	for (pos_int i = 0; i < num_col; ++i){
		//sleep(1);
		generate_rand(&columns[i].vector,size_col);
		columns[i].size=size_col;
		columns[i].identifier=i;
	}

	mdata* md;
	chunkify(&md, columns, size_chunk, num_col);

	p->startPerf();
	sleep(1);
	t->start();	
	
	DataCanopy* dc = new DataCanopy(md);
	dc->BuildLevelOne();
	
	//dc->BuildLevelTwo();
	
	//dc->BuildLevelOneTwo();

	cout<<dc->GetCanopySize()<<",,canopy_size"<<endl;
	
	t->end();
	cout<<t->getDiff()<<",,level_one_time"<<endl;


	
	t->start();
	dc->BuildLevelTwo();
	t->end();
	cout<<t->getDiff()<<",,level_two_time"<<endl;
	p->endPerf();
	//pretty_print_md(md);

/*#ifdef PROBE
	DataCanopy* dc = new DataCanopy(md);
	dc->makeCanopyCacheFriendly();
#endif

	p->startPerf();
	sleep(1);
	t->start();
#ifndef PROBE
	DataCanopy* dc = new DataCanopy(md);
	dc->makeCanopyCacheFriendly();
#endif

#ifdef PROBE
	dc->probeCanopy();
#endif
	
	t->end();
	p->endPerf();*/


	
	cout<<t->getDiff()<<",,time"<<endl;
	cout<<"***"<<endl;




}
