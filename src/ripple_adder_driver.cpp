#include "ripple_adder_driver.hpp"

ripple_adder_driver::ripple_adder_driver(sc_core::sc_module_name)
{
  SC_THREAD(prc_driver);
}

void ripple_adder_driver::prc_driver()
{
  sc_uint<9> pattern; // 4-bit A, 4-bit B, C0
  d_a0 = 0;
  d_a1 = 0;
  d_a2 = 0;
  d_a3 = 0;
  d_b0 = 0;
  d_b1 = 0;
  d_b2 = 0;
  d_b3 = 0;
  d_c0 = 0;
  pattern = 0;
  do
    {
      wait(5, SC_NS);
      pattern++;
      d_a0 = pattern[0];
      d_a1 = pattern[1];
      d_a2 = pattern[2];
      d_a3 = pattern[3];
      d_b0 = pattern[4];
      d_b1 = pattern[5];
      d_b2 = pattern[6];
      d_b3 = pattern[7];
      d_c0 = pattern[8];
    }
  while(0x1FF != pattern);
  wait(5, SC_NS);
  sc_stop();
}
