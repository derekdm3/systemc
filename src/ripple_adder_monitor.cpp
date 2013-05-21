#include <iostream>
#include <iomanip>
#include "ripple_adder_monitor.hpp"

ripple_adder_monitor::ripple_adder_monitor(sc_core::sc_module_name)
{
  SC_METHOD(prc_monitor);
  sensitive
    << m_a0
    << m_a1
    << m_a2
    << m_a3
    << m_b0
    << m_b1
    << m_b2
    << m_b3
    << m_c0
    << m_s0
    << m_s1
    << m_s2
    << m_s3
    << m_c4;
  std::cout
    << "|a0"
    << "|a1"
    << "|a2"
    << "|a3"
    << "|b0"
    << "|b1"
    << "|b2"
    << "|b3"
    << "|c0"
    << "|s0"
    << "|s1"
    << "|s2"
    << "|s3"
    << "|c4"
    << "|\n";
}

void ripple_adder_monitor::prc_monitor()
{
  std::cout
    << "| " << m_a0
    << "| " << m_a1
    << "| " << m_a2
    << "| " << m_a3
    << "| " << m_b0
    << "| " << m_b1
    << "| " << m_b2
    << "| " << m_b3
    << "| " << m_c0
    << "| " << m_s0
    << "| " << m_s1
    << "| " << m_s2
    << "| " << m_s3
    << "| " << m_c4
    << "|\n";
}
