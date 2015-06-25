#include <time.h>
#include <iostream>

class timer{

private:
	timespec ts_beg;
	timespec ts_end;

public:
	timer();	
	void start();
	void end();
	void printDiff();
	float getDiff();

};

timer::timer(){

}

void timer::start(){
	//ts_beg=0;
	
	clock_gettime(CLOCK_REALTIME, &ts_beg);
}

void timer::end(){
	//ts_end=0;	
	clock_gettime(CLOCK_REALTIME, &ts_end);

}

void timer::printDiff(){
	std::cout << (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9 << "";

}

float timer::getDiff(){
	return (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9;
}