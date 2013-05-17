#include "full_adder_driver.hpp"
#include "full_adder_monitor.hpp"
#include "full_adder.hpp"

int sc_main(int argc, char* argv[])
{
    sc_signal<bool> t_a;
    sc_signal<bool> t_b;
    sc_signal<bool> t_cin;
    sc_signal<bool> t_sum;
    sc_signal<bool> t_cout;
    // helps debug to use consistent instance name
    full_adder f1("f1");
    f1.a(t_a);
    f1.b(t_b);
    f1.carry_in(t_cin);
    f1.sum(t_sum);
    f1.carry_out(t_cout);
    full_adder_driver d1("d1");
    d1.d_a(t_a);
    d1.d_b(t_b);
    d1.d_cin(t_cin);
    full_adder_monitor mo1("mo1");
    mo1.m_a(t_a);
    mo1.m_b(t_b);
    mo1.m_cin(t_cin);
    mo1.m_sum(t_sum);
    mo1.m_cout(t_cout);
    // simulate for max 100 ns
    sc_start(100, SC_NS);
    return 0;
}
