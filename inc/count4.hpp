// File: count4.hpp

#include <systemc.h>

SC_MODULE(count4)
{
   SC_HAS_PROCESS(count4);

   const static int COUNT_SIZE = 4;

   sc_in<bool> mclk;
   sc_in<bool> clear;
   sc_in<bool> updown;

   sc_out<sc_uint<COUNT_SIZE> > data_out;

   count4(sc_module_name);

   void sync_block();
};
