//! \file memory.hpp

#include <systemc.h>

SC_MODULE(memory)
{
   SC_HAS_PROCESS(memory);

   const static int WORD_SIZE = 8;
   const static int ADDR_SIZE = 6;
   const static int MEM_SIZE = 100;

   sc_in<bool> en;
   sc_in<bool> rw;
   sc_in<bool> clk;
   sc_in<sc_uint<ADDR_SIZE> > addr;
   sc_inout<sc_lv<WORD_SIZE> > data;
   sc_lv<WORD_SIZE> ram[MEM_SIZE];

   memory(sc_module_name);

   void prc_memory();
};
