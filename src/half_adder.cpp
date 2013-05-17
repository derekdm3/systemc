#include "half_adder.hpp"

half_adder::half_adder(sc_core::sc_module_name)
{
    SC_METHOD(prc_half_adder);
    sensitive << a << b;
}

void half_adder::prc_half_adder()
{
    sum = a ^ b;
    carry = a & b;
}
