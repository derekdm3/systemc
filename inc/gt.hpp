// File: gt.hpp

#include <systemc.h>

struct gt : sc_core::sc_module
{
   typedef gt SC_CURRENT_USER_MODULE;

   const static int WIDTH = 8;

   sc_in<sc_uint<WIDTH> > a;
   sc_in<sc_uint<WIDTH> > b;

   sc_out<bool> z;

   gt(sc_core::sc_module_name);

   void prc_gt();
};
