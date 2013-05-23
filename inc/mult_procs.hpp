// File: mult_procs.hpp

#include <systemc.h>

struct mult_procs : sc_core::sc_module
{
   typedef mult_procs SC_CURRENT_USER_MODULE;

   sc_in<bool> source;
   sc_out<bool> drain;

   sc_signal<bool> connect1;
   sc_signal<bool> connect2;

   mult_procs(sc_core::sc_module_name);

   void prc_mult_procs1();
   void prc_mult_procs2();
   void prc_mult_procs3();
};
