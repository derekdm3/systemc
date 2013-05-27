//! \file generic_instantiate.cpp

#include "generic_instantiate.hpp"

generic_instantiate::generic_instantiate(sc_core::sc_module_name)
   : and2("and2")
   , and4("and4")
{
   SC_METHOD(prc_xor);
   sensitive << and2out << and4out;
   SC_METHOD(prc_splitter);
   sensitive << tsq;
   and2.a(t2);
   and2.z(and2out);
   and4.a(t4);
   and4.z(and4out);
}

void generic_instantiate::prc_xor()
{
   rsq = and2out ^ and4out;
}

void generic_instantiate::prc_splitter()
{
   sc_uint<WIDTH> temp = tsq.read();
   t2 = temp.range(0, 1);
   t4 = temp.range(2, 5);
}
