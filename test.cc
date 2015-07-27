#include <math.h>

#include "config.h"
#include "canopy.hh"
#include "canopyBuilder.hh"
#include "generator.hh"
#include "./tools/run_perf.hh"
#include "./tools/timer.hh"

using namespace std;


int main(int argc,  char** argv){

	
	if(argc !=5)
		return -1;

	perfProfiler* p = new perfProfiler("cycles,cache-misses",false);
	timer* t = new timer();
	timer* total_t = new timer();

	pos_int num_col = atoi(argv[1]); 
	pos_int size_col = atoi(argv[2]);
	pos_int size_chunk = atoi(argv[3]);
	int num_threads = atoi(argv[4]);

	cout<<num_col<<",,num_col"<<endl;
	cout<<size_col<<",,size_col"<<endl;
	cout<<size_chunk<<",,size_chunk"<<endl;
	cout<<num_threads<<",,num_threads"<<endl;

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
		total_t->start();
	
			DataCanopy* dc = new DataCanopy(md);
			CanopyBuilder* cb = new CanopyBuilder(dc,num_threads);
			
			/***/
			t->start();
				cb->BuildLevelOne();
			t->end();

			cout<<t->getDiff()<<",,level_one_time"<<endl;
			cout<<dc->GetCanopySize()<<",,canopy_size"<<endl;

#ifdef INSERT
			assert(dc->GetCanopySize()==( md->num_col * md->num_chun) );
#endif
			/***/

			/***/
			t->start();
				cb->BuildLevelTwo();
			t->end();

			cout<<t->getDiff()<<",,level_two_time"<<endl;
			cout<<dc->GetCanopySize()<<",,canopy_size"<<endl;

#ifdef INSERT
			assert(dc->GetCanopySize()==( (md->num_col + ((md->num_col)*(md->num_col-1)/2) ) * md->num_chun ) );
#endif			
			/***/
			t->start();
				cb->BuildAll();
			t->end();
			
			cout<<t->getDiff()<<",,rest_of_levels_time"<<endl;
			cout<<dc->GetCanopySize()<<",,canopy_size"<<endl;

#ifdef INSERT
		assert(dc->GetCanopySize()==( (pow( 2,md->num_col) -1 ) * md->num_chun) );
#endif
		
		total_t->end();
		
		cout<<total_t->getDiff()<<",,total_time"<<endl;
		
		cout<<dc->GetCanopySize()<<",,canopy_size"<<endl;

		


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


	

	cout<<"***"<<endl;




}
