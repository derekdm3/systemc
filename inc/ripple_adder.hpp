#include "full_adder.hpp"

struct ripple_adder : sc_core::sc_module
{
    typedef ripple_adder SC_CURRENT_USER_MODULE;

    sc_in<bool> a0;
    sc_in<bool> a1;
    sc_in<bool> a2;
    sc_in<bool> a3;

    sc_in<bool> b0;
    sc_in<bool> b1;
    sc_in<bool> b2;
    sc_in<bool> b3;

    sc_in<bool> c0;

    sc_out<bool> s0;
    sc_out<bool> s1;
    sc_out<bool> s2;
    sc_out<bool> s3;

    sc_out<bool> c4;

    sc_signal<bool> c1;
    sc_signal<bool> c2;
    sc_signal<bool> c3;
    
    full_adder f0;
    full_adder f1;
    full_adder f2;
    full_adder f3;

    ripple_adder(sc_core::sc_module_name);

    void prc_or();
};
