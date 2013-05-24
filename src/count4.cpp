// File: count4.cpp

#include "count4.hpp"

count4::count4(sc_core::sc_module_name)
{
   SC_METHOD(sync_block);
   sensitive << mclk.pos() << clear.neg();
}

void count4::sync_block()
{
   if(!clear)
   {
      data_out.write(0);
   }
   else if(updown)
   {
      data_out.write(data_out.read() + 1);
   }
   else
   {
      data_out.write(data_out.read() - 1);
   }
}
