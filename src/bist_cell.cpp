#include "bist_cell.hpp"

bist_cell::bist_cell(sc_core::sc_module_name)
{
   SC_METHOD(prc_bist_cell);
   sensitive << b0 << b1 << d0 << d1;
}

void bist_cell::prc_bist_cell()
{
   //z = !((!(d0 & b1) & !(b0 & d1)) |
   //      !(!(d0 & b1) | !(b0 & d1)));

   bool s1;
   bool s2;
   bool s3;

   s1 = !(b0 & d1);
   s2 = !(d0 & b1);
   s3 = !(s2 | s1);
   s2 = s2 & s1;
   z = !(s2 | s3);
}
