
#########################################################################
COMPILER         = g++
OPTIMIZATION_OPT = -O0
OPTIONS          = -g -ggdb -pthread -W -Wall -lnuma -lrt -ltbb -W -Wno-write-strings -Wno-long-long -std=gnu++11 -Iinclude $(OPTIMIZATION_OPT)
LINKER_OPT       = -L/usr/lib -lstdc++
#VEC_FLAGS		 = -msse2 -msse4.1 -mpclmul
#PROBE_T			 = 256
##########################################################################

##########################################################################
PREDEF		 	 = -D
OUT_DIR          = ./bin/
INCLUDE_DIR		 = ./include/


# All the header files to include in the compilation

INCLUDE = $(INCLUDE_DIR)data.hh $(INCLUDE_DIR)generator.hh $(INCLUDE_DIR)canopy.hh $(INCLUDE_DIR)config.h $(INCLUDE_DIR)canopyBuilder.hh $(INCLUDE_DIR)canopyInteractor.hh
DC 	= data.cc generator.cc test.cc canopy.cc canopyBuilder.cc canopyInteractor.cc

BUILD+=DATA_CANOPY_INTERACT
#BUILD+=DATA_CANOPY_DEMO
BUILD+=DATA_CANOPY_TEST



all: $(BUILD)

DEFINE_1=-DPRINT_FOR_PLOTTING
DATA_CANOPY_TEST: $(INCLUDE)
	$(COMPILER) $(OPTIONS) -o $(OUT_DIR)dc_test $(DC) $(LINKER_OPT) $(DEFINE_1)

DEFINE_2=-DINTERACT
DATA_CANOPY_INTERACT: $(DEP)
	$(COMPILER) $(OPTIONS) -o $(OUT_DIR)dc_interact $(DC) $(LINKER_OPT) $(DEFINE_2)

#DEFINE_3=-DPRINT_FOR_DEMO_INTERACT
#DATA_CANOPY_DEMO: $(DEP)
#	$(COMPILER) $(OPTIONS) -o $(OUT_DIR)demo_interact $(DC) $(LINKER_OPT) $(DEFINE_3)




clean:

	







