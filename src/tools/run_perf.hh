#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

using namespace std;

void* status;

class perfProfiler{

private:
	char* events;
	void runPerf();
	int perf_id;
	bool power;
public:
	perfProfiler(char* e,bool p);
	void startPerf();
	void endPerf();
};



perfProfiler::perfProfiler(char* e,bool p){
	events=e;
	power=p;
}

void perfProfiler::runPerf(){

	int perf_pid = getppid();
    char perf_pid_opt[9];
    snprintf(perf_pid_opt, 24, "%d", perf_pid);
    char *perfargs_system[8] = {"perf", "stat", "-a", "-x,", "-e",
        	events, NULL,NULL};
    
    char *perfargs[9] = {"perf", "stat", "-x,", "-e",
        	events, "-p",
        	perf_pid_opt, NULL,NULL};
    //char *perfargs[6] = {"perf", "stat" ,"-x,", "-e",
      //  	events};
    //if (power)
    	//char *perfargs[6] = {"perf", "stat", "-a" ,"-x,", "-e",
        //	events};
    if (power)	
    	execvp("perf", perfargs_system);
    else
    	execvp("perf", perfargs);
    assert(0 && "perf failed to start");

}

/*
*	Use this function to fork a process that runs perf and attaches it to 
*	the current process.
* */
void perfProfiler::startPerf(){
	int pid = fork();

	if(pid>0){
		perf_id = pid;
		return;
	}else if(pid == 0){
		runPerf();
	}
	return;
}

/*
*	Use this function to stop profiling using perf
* */

void perfProfiler::endPerf(){
	int status =0 ;
	kill(perf_id, SIGINT);
	wait(&status);
}
