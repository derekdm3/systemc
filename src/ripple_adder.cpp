#include "ripple_adder.hpp"

ripple_adder::ripple_adder(sc_core::sc_module_name)
  : f0("f0")
  , f1("f1")
  , f2("f2")
  , f3("f3")
{
  f0.a(a0);
  f0.b(b0);
  f0.carry_in(c0);
  f0.sum(s0);
  f0.carry_out(c1);

  f1.a(a1);
  f1.b(b1);
  f1.carry_in(c1);
  f1.sum(s1);
  f1.carry_out(c2);

  f2.a(a2);
  f2.b(b2);
  f2.carry_in(c2);
  f2.sum(s2);
  f2.carry_out(c3);

  f3.a(a3);
  f3.b(b3);
  f3.carry_in(c3);
  f3.sum(s3);
  f3.carry_out(c4);

  //SC_METHOD(prc_or);
  sensitive << c1 << c2 << c3;
}

void ripple_adder::prc_or()
{
  //carry_out = c1 | c2;
}
