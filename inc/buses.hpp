//! \file buses.hpp

#include <systemc.h>

SC_MODULE(buses)
{
   SC_HAS_PROCESS(buses);

   const static int BUS_SIZE = 4;

   sc_in<bool> a_ready;
   sc_in<bool> b_ready;
   sc_in<sc_uint<BUS_SIZE> > a_bus;
   sc_in<sc_uint<BUS_SIZE> > b_bus;
   sc_out_rv<BUS_SIZE> z_bus; //! resolved port

   buses(sc_module_name);

   void prc_a_bus();
   void prc_b_bus();
};
