#include <systemc.h>

struct full_adder_monitor : sc_core::sc_module
{
    typedef full_adder_monitor SC_CURRENT_USER_MODULE;

    sc_in<bool> m_a;
    sc_in<bool> m_b;
    sc_in<bool> m_cin;
    sc_in<bool> m_sum;
    sc_in<bool> m_cout;

    full_adder_monitor(sc_core::sc_module_name);

    void prc_monitor();
};
