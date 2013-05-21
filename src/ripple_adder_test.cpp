#include "ripple_adder_driver.hpp"
#include "ripple_adder_monitor.hpp"
#include "ripple_adder.hpp"

int sc_main(int argc, char* argv[])
{
    sc_signal<bool> t_a0;
    sc_signal<bool> t_a1;
    sc_signal<bool> t_a2;
    sc_signal<bool> t_a3;
    sc_signal<bool> t_b0;
    sc_signal<bool> t_b1;
    sc_signal<bool> t_b2;
    sc_signal<bool> t_b3;
    sc_signal<bool> t_c0;
    sc_signal<bool> t_s0;
    sc_signal<bool> t_s1;
    sc_signal<bool> t_s2;
    sc_signal<bool> t_s3;
    sc_signal<bool> t_c4;
    ripple_adder r0("r0");
    r0.a0(t_a0);
    r0.a1(t_a1);
    r0.a2(t_a2);
    r0.a3(t_a3);
    r0.b0(t_b0);
    r0.b1(t_b1);
    r0.b2(t_b2);
    r0.b3(t_b3);
    r0.c0(t_c0);
    r0.s0(t_s0);
    r0.s1(t_s1);
    r0.s2(t_s2);
    r0.s3(t_s3);
    r0.c4(t_c4);
    ripple_adder_driver d0("d0");
    d0.d_a0(t_a0);
    d0.d_a1(t_a1);
    d0.d_a2(t_a2);
    d0.d_a3(t_a3);
    d0.d_b0(t_b0);
    d0.d_b1(t_b1);
    d0.d_b2(t_b2);
    d0.d_b3(t_b3);
    d0.d_c0(t_c0);
    ripple_adder_monitor m0("m0");
    m0.m_a0(t_a0);
    m0.m_a1(t_a1);
    m0.m_a2(t_a2);
    m0.m_a3(t_a3);
    m0.m_b0(t_b0);
    m0.m_b1(t_b1);
    m0.m_b2(t_b2);
    m0.m_b3(t_b3);
    m0.m_c0(t_c0);
    m0.m_s0(t_s0);
    m0.m_s1(t_s1);
    m0.m_s2(t_s2);
    m0.m_s3(t_s3);
    m0.m_c4(t_c4);
    // simulate for max 1000 ns
    sc_start(1, SC_SEC);
    return 0;
}
