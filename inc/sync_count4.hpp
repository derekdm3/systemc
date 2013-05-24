// File: sync_count4.hpp

#include <systemc.h>

SC_MODULE(sync_count4)
{
   SC_HAS_PROCESS(sync_count4);

   const static int COUNT_BITS = 4;

   sc_in<bool> mclk;
   sc_in<bool> preset;
   sc_in<bool> updown;

   sc_in<sc_uint<COUNT_BITS> > data_in;
   sc_out<sc_uint<COUNT_BITS> > data_out;

   sync_count4(sc_module_name);

   void prc_counter();
};
