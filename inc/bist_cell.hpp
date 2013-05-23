#include <systemc.h>

// built-in self-test module

struct bist_cell : sc_core::sc_module
{
   typedef bist_cell SC_CURRENT_USER_MODULE;

   sc_in<bool> b0;
   sc_in<bool> b1;
   sc_in<bool> d0;
   sc_in<bool> d1;

   sc_out<bool> z;

   bist_cell(sc_core::sc_module_name);

   void prc_bist_cell();
};
