// File: async_states.cpp

#include "async_states.hpp"

async_states::async_states(sc_core::sc_module_name)
{
   SC_METHOD(prc_async_states);
   sensitive << clk.neg() << reset.neg() << set.pos();
}

void async_states::prc_async_states()
{
   if(!reset)
   {
      next_state.write(0);
   }
   else if(set)
   {
      next_state.write(5);
   }
   else
   {
      next_state.write(current_state.read());
   }
}
