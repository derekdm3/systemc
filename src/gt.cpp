// File: gt.cpp

#include "gt.hpp"

gt::gt(sc_core::sc_module_name)
{
   SC_METHOD(prc_gt);
   sensitive << a << b;
}

void gt::prc_gt()
{
   // local values necessary, range disallowed on ports
   //sc_uint<WIDTH> l_a = a.read();
   //sc_uint<WIDTH> l_b = b.read();
   // cast range result to ensure uint values
   z = sc_uint<WIDTH>(a.read().range(WIDTH / 2 - 1, 0)) >
       sc_uint<WIDTH>(b.read().range(WIDTH - 1, WIDTH / 2));
}
