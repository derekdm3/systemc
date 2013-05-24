// File: sync_count4.cpp

#include "sync_count4.hpp"

sync_count4::sync_count4(sc_core::sc_module_name)
{
   SC_METHOD(prc_counter);
   sensitive << mclk.pos();
}

void sync_count4::prc_counter()
{
   if(!preset)
   {
      data_out.write(data_in.read());
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
