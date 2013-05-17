#include <iostream>
#include <iomanip>
#include "full_adder_monitor.hpp"

full_adder_monitor::full_adder_monitor(sc_core::sc_module_name)
{
    SC_METHOD(prc_monitor);
    sensitive
        << m_a
        << m_b
        << m_cin
        << m_sum
        << m_cout;
    std::cout << "|Inputs |Outputs|\n";
    std::cout << "|A|B|Cin|Cout|S |\n";
}

void full_adder_monitor::prc_monitor()
{
    std::cout << "|" << m_a << "|" << m_b << "|" << m_cin << "  |" << m_cout << "   |" << m_sum << " |\n";
}
