// File: basic_ff.cpp

#include "basic_ff.hpp"

basic_ff::basic_ff(sc_core::sc_module_name)
{
   SC_METHOD(prc_basic_ff);
   sensitive << clk.pos(); // pos edge triggered
}

void basic_ff::prc_basic_ff()
{
   q = d;
}
