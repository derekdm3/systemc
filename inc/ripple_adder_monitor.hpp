#include <systemc.h>

struct ripple_adder_monitor : sc_core::sc_module
{
    typedef ripple_adder_monitor SC_CURRENT_USER_MODULE;

    sc_in<bool> m_a0;
    sc_in<bool> m_a1;
    sc_in<bool> m_a2;
    sc_in<bool> m_a3;

    sc_in<bool> m_b0;
    sc_in<bool> m_b1;
    sc_in<bool> m_b2;
    sc_in<bool> m_b3;

    sc_in<bool> m_c0;

    sc_in<bool> m_s0;
    sc_in<bool> m_s1;
    sc_in<bool> m_s2;
    sc_in<bool> m_s3;

    sc_in<bool> m_c4;

    ripple_adder_monitor(sc_core::sc_module_name);

    void prc_monitor();
};
