#include "full_adder.hpp"

full_adder::full_adder(sc_core::sc_module_name)
    : ha1("ha1")
    , ha2("ha2")
{
    ha1.a(a);
    ha1.b(b);
    ha1.sum(s1);
    ha1.carry(c1);
    ha2.a(s1);
    ha2.b(carry_in);
    ha2.sum(sum);
    ha2.carry(c2);
    SC_METHOD(prc_or);
    sensitive << c1 << c2;
}

void full_adder::prc_or()
{
    carry_out = c1 | c2;
}
