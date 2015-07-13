
#include "canopyBuilder.hh"

void* thread_BuildThreaded(void* input){


	threadInput* in = (threadInput*) input;

	if(in->buildMode == 1)
		in->dc->BuildLevelOne(in->start_chunk,in->end_chunk);

	if(in->buildMode == 2)
		in->dc->BuildLevelTwo(in->start_chunk,in->end_chunk);

	if(in->buildMode == 12)
		in->dc->BuildLevelOneTwo(in->start_chunk,in->end_chunk);

	if(in->buildMode == 3)
		in->dc->BuildAll(in->start_chunk,in->end_chunk);

	return 0;
}

int CanopyBuilder::BuildThreaded(int buildMode){
	
	pthread_t threads[nthreads];
	threadInput inputs[nthreads];

	int chunks_per_thread = canopy->GetNumChunk() / nthreads;

	for (int i = 0; i < nthreads; ++i){
		
		inputs[i].dc = canopy;
		inputs[i].buildMode = buildMode;
		inputs[i].start_chunk=i*chunks_per_thread;
		inputs[i].end_chunk=(i+1)*chunks_per_thread;
		if(i==nthreads-1)
			inputs[i].end_chunk=canopy->GetNumChunk();
		cout<<inputs[i].start_chunk<<" "<<inputs[i].end_chunk<<endl;
		pthread_create(&threads[i], NULL, *thread_BuildThreaded,(void*)&inputs[i]);
	}
	return 0;

}

int CanopyBuilder::BuildLevelOne(){
	BuildThreaded(1);
	return 1;

}

int CanopyBuilder::BuildLevelTwo(){
	BuildThreaded(2);
	return 1;

}

int CanopyBuilder::BuildLevelOneTwo(){
	BuildThreaded(12);
	return 1;

}

int CanopyBuilder::BuildAll(){
	BuildThreaded(3);
	return 1;

}

