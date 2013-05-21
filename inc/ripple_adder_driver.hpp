#include <systemc.h>

struct ripple_adder_driver : sc_core::sc_module
{
    typedef ripple_adder_driver SC_CURRENT_USER_MODULE;

    sc_out<bool> d_a0;
    sc_out<bool> d_a1;
    sc_out<bool> d_a2;
    sc_out<bool> d_a3;

    sc_out<bool> d_b0;
    sc_out<bool> d_b1;
    sc_out<bool> d_b2;
    sc_out<bool> d_b3;

    sc_out<bool> d_c0;

    ripple_adder_driver(sc_core::sc_module_name);

    void prc_driver();
};
