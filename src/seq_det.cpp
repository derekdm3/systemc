// File: seq_det.cpp

#include "seq_det.hpp"

seq_det::seq_det(sc_core::sc_module_name)
{
   SC_METHOD(prc_seq_det);
   // edge sensitivity
   sensitive << clk.pos();
   SC_METHOD(prc_output);
   // event sensitivity
   sensitive << first << second << third;
}

void seq_det::prc_seq_det()
{
   first = data;
   second = first;
   third = second;
}

void seq_det::prc_output()
{
   seq_found = first & (!second) & third;
}
