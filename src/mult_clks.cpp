// File: mult_clks.cpp

#include "mult_clks.hpp"

mult_clks::mult_clks(sc_core::sc_module_name)
{
   SC_METHOD(prc_vt15ck);
   sensitive << vt15ck.neg();
   SC_METHOD(prc_ds1ck);
   sensitive << ds1ck.pos();
}

void mult_clks::prc_vt15ck()
{
   add_state = !(addclk | (adn | resetn));
   sub_state = subclr ^ (subn & resetn);
}

void mult_clks::prc_ds1ck()
{
   ds1_add = add_state;
   ds1_sub = sub_state;
}
