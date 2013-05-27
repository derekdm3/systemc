//! \file memory.cpp

#include "memory.hpp"

memory::memory(sc_core::sc_module_name)
{
   SC_METHOD(prc_memory);
   sensitive << clk.neg();
}

void memory::prc_memory()
{
   sc_lv<WORD_SIZE> allzs(SC_LOGIC_Z);
   sc_lv<WORD_SIZE> allxs(SC_LOGIC_X);
   if(en)
   {
      if(addr.read() < MEM_SIZE)
      {
         if(rw)
         {
            data.write(ram[addr.read()]);
         }
         else
         {
            ram[addr.read()] = data.read();
         }
      }
      else if(rw)
      {
         data.write(allxs);
      }
   }
   else
   {
      data.write(allzs);
   }
}
