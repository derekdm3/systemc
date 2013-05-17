#include "half_adder.hpp"

struct full_adder : sc_core::sc_module
{
    typedef full_adder SC_CURRENT_USER_MODULE;

    sc_in<bool> a;
    sc_in<bool> b;
    sc_in<bool> carry_in;
    sc_out<bool> sum;
    sc_out<bool> carry_out;

    sc_signal<bool> c1;
    sc_signal<bool> s1;
    sc_signal<bool> c2;

    half_adder ha1;
    half_adder ha2;

    full_adder(sc_core::sc_module_name);

    void prc_or();
};
