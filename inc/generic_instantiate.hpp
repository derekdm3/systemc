//! \file generic_instantiate.hpp

#include "generic_and.hpp"

SC_MODULE(generic_instantiate)
{
   SC_HAS_PROCESS(generic_instantiate);

   const static int WIDTH = 6;

   sc_in<sc_uint<WIDTH> > tsq;
   sc_out<bool> rsq;
   generic_and<2> and2;
   generic_and<4> and4;
   sc_signal<bool> and2out;
   sc_signal<bool> and4out;
   sc_signal<sc_uint<2> > t2;
   sc_signal<sc_uint<4> > t4;

   generic_instantiate(sc_module_name);

   void prc_xor();
   void prc_splitter();
};
