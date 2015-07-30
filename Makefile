
COMPILER         = g++
OPTIMIZATION_OPT = -O3
OPTIONS          = -g -ggdb -pthread -W -Wall -lnuma -lrt -ltbb -W -Wno-long-long -std=gnu++11 $(OPTIMIZATION_OPT)
LINKER_OPT       = -L/usr/lib -lstdc++
#VEC_FLAGS		 = -msse2 -msse4.1 -mpclmul
#PROBE_T			 = 256

PREDEF		 	 = -D
OUT_DIR          = ./bin/

DEP = data.hh generator.hh canopy.hh config.h canopyBuilder.hh
DC 	= data.cc generator.cc test.cc canopy.cc canopyBuilder.cc

#BUILD+=DATA_CANOPY_TEST
BUILD+=DATA_CANOPY_DEMO



all: $(BUILD)

#DEFINE_1=-DPRINT_FOR_PLOTTING
#DATA_CANOPY_TEST: $(DEP)
#	$(COMPILER) $(OPTIONS) -o $(OUT_DIR)test $(DC) $(LINKER_OPT) $(DEFINE_1)

#DEFINE_2=-DPRINT_FOR_DEMO
#DATA_CANOPY_DEMO: $(DEP)
#	$(COMPILER) $(OPTIONS) -o $(OUT_DIR)demo_performance $(DC) $(LINKER_OPT) $(DEFINE_2)

DEFINE_3=-DPRINT_FOR_DEMO_INTERACT
DATA_CANOPY_DEMO: $(DEP)
	$(COMPILER) $(OPTIONS) -o $(OUT_DIR)demo_interact $(DC) $(LINKER_OPT) $(DEFINE_3)




clean:

	
#
# The End !
#








