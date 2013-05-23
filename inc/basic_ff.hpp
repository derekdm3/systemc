// File: basic_ff.hpp

#include <systemc.h>

struct basic_ff : sc_core::sc_module
{
   typedef basic_ff SC_CURRENT_USER_MODULE;

   sc_in<bool> d;
   sc_in<bool> clk;

   sc_out<bool> q;

   basic_ff(sc_core::sc_module_name);

   void prc_basic_ff();
};
