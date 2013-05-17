#include "full_adder_driver.hpp"

full_adder_driver::full_adder_driver(sc_core::sc_module_name)
{
    SC_THREAD(prc_driver);
}

void full_adder_driver::prc_driver()
{
    sc_uint<3> pattern;
    d_a = 0;
    d_b = 0;
    d_cin = 0;
    pattern = 0;
    do
    {
        wait(5, SC_NS);
        pattern++;
        d_a = pattern[2];
        d_b = pattern[1];
        d_cin = pattern[0];
    }
    while(7 != pattern);
    wait(5, SC_NS);
    sc_stop();
}
