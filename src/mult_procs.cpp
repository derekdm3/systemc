// File: mult_procs.cpp

#include "mult_procs.hpp"

mult_procs::mult_procs(sc_core::sc_module_name)
{
   SC_METHOD(prc_mult_procs1);
   SC_METHOD(prc_mult_procs2);
   SC_METHOD(prc_mult_procs3);
   sensitive << source;
   sensitive << connect1;
   sensitive << connect2;
}

void mult_procs::prc_mult_procs1()
{
   connect1 = !source;
}

void mult_procs::prc_mult_procs2()
{
   connect2 = !connect1;
}

void mult_procs::prc_mult_procs3()
{
   drain = !connect2;
}
