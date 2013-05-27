//! \file generic_and.hpp

#include <systemc.h>

template <int SIZE>
SC_MODULE(generic_and)
{
   SC_HAS_PROCESS(generic_and);

   sc_in<sc_uint<SIZE> > a;
   sc_out<bool> z;

   generic_and(sc_module_name)
   {
      SC_METHOD(prc_generic_and);
      sensitive << a;
   }

   inline void prc_generic_and()
   {
      sc_bv<SIZE> bv_temp = a.read();
      z = bv_temp.and_reduce();
   }
};
