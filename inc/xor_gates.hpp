// File: xor_gates.hpp

#include <systemc.h>

struct xor_gates : sc_core::sc_module
{
   typedef xor_gates SC_CURRENT_USER_MODULE;

   const static int SIZE = 4;

   sc_in<sc_uint<SIZE> > bre;
   sc_in<sc_uint<SIZE> > sty;

   sc_out<sc_uint<SIZE> > tap;

   xor_gates(sc_core::sc_module_name);

   void prc_xor_gates();
};
