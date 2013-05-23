// File: unsigned_adder.cpp

#include "unsigned_adder.hpp"

unsigned_adder::unsigned_adder(sc_core::sc_module_name)
{
   SC_METHOD(prc_unsigned_adder);
   sensitive << arb << tbe;
}

void unsigned_adder::prc_unsigned_adder()
{
   sum = arb.read() + tbe.read();
}
