// File: unsigned_adder.hpp

#include <systemc.h>

struct unsigned_adder : sc_core::sc_module
{
   typedef unsigned_adder SC_CURRENT_USER_MODULE;

   const static int SIZE = 4;

   sc_in<sc_uint<SIZE> > arb;
   sc_in<sc_uint<SIZE> > tbe;

   sc_out<sc_uint<SIZE + 1> > sum;

   unsigned_adder(sc_core::sc_module_name);

   void prc_unsigned_adder();
};
