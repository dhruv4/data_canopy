#include <math.h>

#include "config.h"
#include "canopy.hh"
#include "canopyBuilder.hh"
#include "generator.hh"
#include "canopyInteractor.hh"
#include "./tools/run_perf.hh"
#include "./tools/timer.hh"

using namespace std;

bool getParam(int argc,char** argv,pos_int* num_col, pos_int* size_col, pos_int* size_chunk, int* num_threads, string* filename, bool* loadFromFile){

	int c;	
	while ((c = getopt (argc, argv, "c:r:s:t:f:")) != -1)
    	switch (c){
      		case 'c':
        		*num_col=atoi(optarg);
        		break;
      		case 'r':
        		*size_col=atoi(optarg);
        		break;
        	case 's':
        		*size_chunk=atoi(optarg);
				break;
        	case 't':
        		*num_threads=atof(optarg);
        		break;
        	case 'f':
        		(filename)->assign(optarg);
        		*loadFromFile=true;
        		break;
      		case '?':
        		if (optopt == 'c')
          			fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        		else if (isprint (optopt))
          			fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        		else
          			fprintf (stderr,
                   		"Unknown option character `\\x%x'.\n",
                   		optopt);
        		return 1;
      		default:
        		abort ();
     	}
  		
  return 0;
}

int main(int argc,  char** argv){


#ifdef PRINT_FOR_PLOTTING

	perfProfiler* p = new perfProfiler("cycles,cache-misses",false);

#endif

	timer* t = new timer();
	timer* total_t = new timer();

	pos_int num_col=0; 
	pos_int size_col=0;
	pos_int size_chunk=0; 
	int num_threads=0;
	string filename;
	bool loadFromFile = false;

	getParam(argc, argv, &num_col, &size_col, &size_chunk, &num_threads, &filename,&loadFromFile);


#ifdef PRINT_FOR_PLOTTING

	cout<<num_col<<",,num_col"<<endl;
	cout<<size_col<<",,size_col"<<endl;
	cout<<size_chunk<<",,size_chunk"<<endl;
	cout<<num_threads<<",,num_threads"<<endl;
	if (loadFromFile){
		cout<<filename<<",,file_name"<<endl;
	}

#endif

	column* columns = (column*)malloc(num_col*sizeof(column));

	if (!loadFromFile){

		for (pos_int i = 0; i < num_col; ++i){
			create_column(&columns[i],i,size_col);
			generate_rand(&columns[i].vector,size_col);
		}

	}else{
	
		load_file(filename.c_str(),&columns,num_col,size_col);
	}

	mdata* md;
	chunkify(&md, columns, size_chunk, num_col);

#ifdef PRINT_FOR_PLOTTING
	p->startPerf();
#endif
	
		sleep(1);
		total_t->start();
	
			DataCanopy* dc = new DataCanopy(md);
			CanopyBuilder* cb = new CanopyBuilder(dc,num_threads);
			
			/***/
			t->start();
				cb->BuildLevelOne();
			t->end();
#ifdef PRINT_FOR_PLOTTING
			cout<<t->getDiff()<<",,level_one_time"<<endl;
			cout<<dc->GetCanopySize()<<",,canopy_size"<<endl;
#endif

#ifdef INSERT
			assert(dc->GetCanopySize()==( md->num_col * md->num_chun) );
#endif
			/***/

			/***/
			t->start();
				cb->BuildLevelTwo();
			t->end();
#ifdef PRINT_FOR_PLOTTING
			cout<<t->getDiff()<<",,level_two_time"<<endl;
			cout<<dc->GetCanopySize()<<",,canopy_size"<<endl;
#endif

#ifdef INSERT
			assert(dc->GetCanopySize()==( (md->num_col + ((md->num_col)*(md->num_col-1)/2) ) * md->num_chun ) );
#endif			
			/***/
			t->start();
				cb->BuildAll();
			t->end();
#ifdef PRINT_FOR_PLOTTING			
			cout<<t->getDiff()<<",,rest_of_levels_time"<<endl;
			cout<<dc->GetCanopySize()<<",,canopy_size"<<endl;
#endif

#ifdef INSERT
		assert(dc->GetCanopySize()==( (pow( 2,md->num_col) -1 ) * md->num_chun) );
#endif
		
		total_t->end();
#ifdef PRINT_FOR_PLOTTING		
		cout<<total_t->getDiff()<<",,total_time"<<endl;
		
		cout<<dc->GetCanopySize()<<",,canopy_size"<<endl;
		p->endPerf();
		cout<<"***"<<endl;

#endif
//pretty_print_cols(columns,num_col);

#ifdef INTERACT

//		cout<<"here"<<endl;

	pretty_print_cols(columns,num_col);


	CanopyInteractor* interactor = new CanopyInteractor(dc);

	/*pos_int* col = new pos_int[2];

	col[0]=1;
	col[1]=2;


	char test[]="1;1;{2}";*/

	interactor->StartTerminal();

#endif

		


	
	
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


	

	



}
