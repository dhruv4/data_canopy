#!/bin/csh
setenv TBBROOT "/home/awasay/data canopy /lib/tbb43_20150611oss" #
setenv tbb_bin "/home/awasay/data canopy /lib/tbb43_20150611oss/build/linux_intel64_gcc_cc4.7_libc2.13_kernel3.18.11_debug" #
if (! $?CPATH) then #
    setenv CPATH "${TBBROOT}/include" #
else #
    setenv CPATH "${TBBROOT}/include:$CPATH" #
endif #
if (! $?LIBRARY_PATH) then #
    setenv LIBRARY_PATH "${tbb_bin}" #
else #
    setenv LIBRARY_PATH "${tbb_bin}:$LIBRARY_PATH" #
endif #
if (! $?LD_LIBRARY_PATH) then #
    setenv LD_LIBRARY_PATH "${tbb_bin}" #
else #
    setenv LD_LIBRARY_PATH "${tbb_bin}:$LD_LIBRARY_PATH" #
endif #
 #
