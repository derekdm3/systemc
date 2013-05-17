#include <systemc.h>

struct full_adder_driver : sc_core::sc_module
{
    typedef full_adder_driver SC_CURRENT_USER_MODULE;

    sc_out<bool> d_a;
    sc_out<bool> d_b;
    sc_out<bool> d_cin;

    full_adder_driver(sc_core::sc_module_name);

    void prc_driver();
};
