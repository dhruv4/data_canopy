
COMPILER         = g++
OPTIMIZATION_OPT = -O3
OPTIONS          = -g -ggdb -pthread -std=c++11 -W -Wall -lnuma -lrt -W -Wno-long-long $(OPTIMIZATION_OPT)
LINKER_OPT       = -L/usr/lib -lstdc++
#VEC_FLAGS		 = -msse2 -msse4.1 -mpclmul
#PROBE_T			 = 256

PREDEF		 	 = -D
OUT_DIR          = ./bin/

DEP = data.hh generator.hh canopy.hh config.h stat.hh
DC 	= data.cc generator.cc test.cc canopy.cc stat.cc

BUILD+=DATA_CANOPY

all: $(BUILD)


DATA_CANOPY: $(DEP)
	$(COMPILER) $(OPTIONS) -o $(OUT_DIR)test $(DC) $(LINKER_OPT) $(DEFINE_1)



clean:

	
#
# The End !
#








