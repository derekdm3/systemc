// File: mult_clks.hpp

#include <systemc.h>

SC_MODULE(mult_clks)
{
   SC_HAS_PROCESS(mult_clks);

   sc_in<bool> vt15ck;
   sc_in<bool> addclk;
   sc_in<bool> adn;
   sc_in<bool> resetn;
   sc_in<bool> subclr;
   sc_in<bool> subn;
   sc_in<bool> ds1ck;

   sc_out<bool> ds1_add;
   sc_out<bool> ds1_sub;

   sc_signal<bool> add_state;
   sc_signal<bool> sub_state;

   mult_clks(sc_core::sc_module_name);

   void prc_vt15ck();
   void prc_ds1ck();
};
