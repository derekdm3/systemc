//! \file tri_state.hpp

#include <systemc.h>

SC_MODULE(tri_state)
{
   SC_HAS_PROCESS(tri_state);

   sc_in<bool> ready;
   sc_in<bool> dina;
   sc_in<bool> dinb;

   sc_out<sc_logic> selectx;

   tri_state(sc_module_name);

   void prc_tri_state();
};
