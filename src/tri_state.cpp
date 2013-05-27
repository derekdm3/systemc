//! \file tri_state.cpp

#include "tri_state.hpp"

tri_state::tri_state(sc_core::sc_module_name)
{
   SC_METHOD(prc_tri_state);
   sensitive << ready << dina << dinb;
}

void tri_state::prc_tri_state()
{
   if(ready)
   {
      selectx = sc_logic('Z');
   }
   else
   {
      selectx = sc_logic(dina.read() & dinb.read());
   }
}
