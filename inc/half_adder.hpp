#include <systemc.h>

struct half_adder : sc_core::sc_module
{
    typedef half_adder SC_CURRENT_USER_MODULE;

    sc_in<bool> a;
    sc_in<bool> b;
    sc_out<bool> sum;
    sc_out<bool> carry;

    half_adder(sc_core::sc_module_name);

    void prc_half_adder();
};
