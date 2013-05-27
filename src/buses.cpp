//! \file buses.cpp

#include "buses.hpp"

buses::buses(sc_core::sc_module_name)
{
   SC_METHOD(prc_a_bus);
   sensitive << a_ready << a_bus;
   SC_METHOD(prc_b_bus);
   sensitive << b_ready << b_bus;
}

void buses::prc_a_bus()
{
   if(a_ready)
   {
      z_bus.write(a_bus.read());
   }
   else
   {
      z_bus.write("ZZZZ");
   }
}

void buses::prc_b_bus()
{
   if(b_ready)
   {
      z_bus.write(b_bus.read());
   }
   else
   {
      z_bus.write("ZZZZ");
   }
}
