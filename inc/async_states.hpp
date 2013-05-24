// File: async_states.hpp

#include <systemc.h>

SC_MODULE(async_states)
{
   SC_HAS_PROCESS(async_states);

   const static int STATE_BITS = 4;

   sc_in<bool> clk;
   sc_in<bool> reset;
   sc_in<bool> set;
   sc_in<sc_uint<STATE_BITS> > current_state;
   sc_out<sc_uint<STATE_BITS> > next_state;

   async_states(sc_core::sc_module_name);

   void prc_async_states();
};
